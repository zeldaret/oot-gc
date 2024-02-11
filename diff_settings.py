def apply(config, args):
    config["baseimg"] = "SIM_S.elf"
    config["myimg"] = "build/SIM/SIM_S.elf"
    config["mapfile"] = "build/SIM/SIM.map"
    config["source_directories"] = ["src", "include"]
    config["arch"] = "ppc"
    config["map_format"] = "mw" # gnu, mw, ms
    config["build_dir"] = "build/SIM/" # only needed for mw and ms map format
    config["objdump_executable"] = "powerpc-eabi-objdump"
