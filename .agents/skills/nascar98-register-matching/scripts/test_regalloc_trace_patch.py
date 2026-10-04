"""Check patch application, source preservation, and refusal of repeat patches."""
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile

helper = Path(__file__).with_name('regalloc_trace_patch.py')
spec = importlib.util.spec_from_file_location('trace_patch', helper)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

if len(sys.argv) < 2:
    raise SystemExit('Usage: test_regalloc_trace_patch.py GLOBAL_C [GLOBAL_C ...]')

for name in sys.argv[1:]:
    source = Path(name).read_text()
    patch = module.trace_patch(source)
    with tempfile.TemporaryDirectory(prefix='n98-trace-test-') as td:
        target = Path(td, 'global.c')
        target.write_text(source)
        subprocess.run(['patch', '-p1'], cwd=td, input=patch, text=True,
                       check=True, capture_output=True)
        changed = target.read_text()
        assert changed.replace(module.ORDER_TRACE, '').replace(module.ASSIGN_TRACE, '') == source
        try:
            module.trace_patch(changed)
        except ValueError:
            pass
        else:
            raise AssertionError('repeat patch accepted')
    print('Patch applies without other source changes:', name)
try:
    module.trace_patch('unknown source')
except ValueError:
    pass
else:
    raise AssertionError('unknown source accepted')
print('Repeat and unknown layouts rejected.')
