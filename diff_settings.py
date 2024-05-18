def add_custom_arguments(parser):
    parser.add_argument("-v", "--version", help="Emulator version to diff", default="ce-j")

def apply(config, args):
    version = args.version
    config["mapfile"] = f"build/{version}/oot-gc.elf.MAP"
    config["source_directories"] = ["src", "include"]
    config["arch"] = "ppc"
    config["map_format"] = "mw" # gnu, mw, ms
    config["build_dir"] = f"build/{version}/src" # only needed for mw and ms map formats
    config["objdump_executable"] = "build/binutils/powerpc-eabi-objdump"
    config["show_line_numbers_default"] = True
