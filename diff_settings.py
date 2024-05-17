def apply(config, args):
    config["mapfile"] = f"build/ce-j/oot-gc.elf.MAP"
    config["source_directories"] = ["src", "include"]
    config["arch"] = "ppc"
    config["map_format"] = "mw" # gnu, mw, ms
    config["build_dir"] = f"build/ce-j/src" # only needed for mw and ms map formats
    config["objdump_executable"] = "tools/objdump_wrapper.py"
    config["show_line_numbers_default"] = True
    config["show_target_line_numbers_default"] = True
