project(LDMXRogue)

# get Rogue::Interface target setup
setup_rogue_target()

setup_library(module Rogue
              dependencies Rogue::Interface)
