#!/usr/bin/env python3
"""Run decomp-permuter on a parked NON_MATCHING draft.

    .venv/bin/python tools/permute.py FUNC [--minutes 10] [PERMUTER_ARGS...]

Sets up nonmatchings/FUNC/ the way the permuter expects: base.c is the
draft's file preprocessed with only that draft switched on and pruned to
the function and what it uses, target.o is the splat asm assembled the
way INCLUDE_ASM assembles it, and compile.sh is the project's own
cpp | cc1 | maspsx | as recipe from `make -n`. Then it runs the permuter
for the given number of minutes. Better candidates land in
nonmatchings/FUNC/output-SCORE-N/source.c; paste the changes back into
the draft and confirm with asm-differ and `make check`.
"""

import argparse
import importlib
import os
import pathlib
import shlex
import signal
import subprocess
import sys

from funcs import invalidate_stale_objects, make_command, parked_drafts

PERMUTER = pathlib.Path("tools/decomp-permuter")
sys.path.insert(0, str(PERMUTER))
permuter_import = importlib.import_module("import")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("func")
    parser.add_argument("--minutes", type=float, default=10,
                        help="stop the permuter after this long")
    args, permuter_args = parser.parse_known_args()

    if invalidate_stale_objects():
        subprocess.run(["make", "build/SLUS_005.21"], check=True)

    found = [
        (src, line)
        for src in sorted(pathlib.Path("src").rglob("*.c"))
        for name, line in parked_drafts(src)
        if name == args.func
    ]
    if not found:
        sys.exit(f"{args.func}: no parked NON_MATCHING draft in src/")
    src, line = found[0]

    work = pathlib.Path("nonmatchings") / args.func
    work.mkdir(parents=True, exist_ok=True)
    lines = src.read_text().splitlines()
    lines[line] = "#if 1"
    variant = work / "variant.c"
    variant.write_text("\n".join(lines) + "\n")

    cc = make_command(f"build/{src}.o", str(src), "cc1")
    cpp = cc.split("|")[0].removeprefix("set -o pipefail;").split()
    cpp = [a for a in cpp if a != str(src)]
    source = subprocess.run(
        cpp + ["-P", str(variant)],
        capture_output=True, text=True, check=True,
    ).stdout
    source, _ = permuter_import.prune_source(source, True, args.func)
    (work / "base.c").write_text(source)

    compile_sh = cc.replace(f" {src} ", ' "$INPUT" ')
    compile_sh = compile_sh.replace(f"-o build/{src}.o", '-o "$OUTPUT"')
    (work / "compile.sh").write_text(
        "#!/usr/bin/env bash\n"
        "set -euo pipefail\n"
        'INPUT="$(realpath "$1")"\n'
        'OUTPUT="$(realpath "$3")"\n'
        f"cd {shlex.quote(str(pathlib.Path.cwd()))}\n"
        f"{compile_sh}\n"
    )
    (work / "compile.sh").chmod(0o755)

    asm = pathlib.Path(f"asm/nonmatchings/{src.stem}/{args.func}.s")
    (work / "target.s").write_text(
        '.include "include/macro.inc"\n'
        ".set noat\n.set noreorder\n.text\n.align 2\n"
        + asm.read_text()
    )
    subprocess.run(
        ["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000",
         "-no-pad-sections", "-O1", "-Iinclude", "-G8",
         "-o", str(work / "target.o"), str(work / "target.s")],
        check=True,
    )

    (work / "settings.toml").write_text(
        f'func_name = "{args.func}"\n'
        'compiler_type = "gcc"\n'
        'objdump_command = "mipsel-linux-gnu-objdump -drz -m mips:3000"\n'
    )

    cmd = [sys.executable, str(PERMUTER / "permuter.py"), str(work),
           "--best-only", "--stop-on-zero"] + (permuter_args or ["-j8"])
    print("$", shlex.join(cmd))
    # The permuter's workers are child processes; stop the whole group.
    proc = subprocess.Popen(cmd, start_new_session=True)
    try:
        proc.wait(timeout=args.minutes * 60)
    except subprocess.TimeoutExpired:
        os.killpg(proc.pid, signal.SIGINT)
        proc.wait()
        print(f"Stopped after {args.minutes:g} minutes.")
    outputs = sorted(work.glob("output-*"),
                     key=lambda p: int(p.name.split("-")[1]))
    print("Best:", outputs[0] / "source.c" if outputs else "no improvement")


if __name__ == "__main__":
    main()
