# asm-differ settings: python3 tools/asm-differ/diff.py -mw FUNC
def apply(config, args):
    config["baseimg"] = "disc/SLUS_005.21"
    config["myimg"] = "build/SLUS_005.21"
    config["mapfile"] = "build/slus_005.21.map"
    config["source_directories"] = ["src", "include"]
    config["arch"] = "mipsel"
    config["map_format"] = "gnu"
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["make_command"] = ["make"]
