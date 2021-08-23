# Set the project name
project(HexaBoard)

# Search for Boost
find_package(
  Boost REQUIRED
  COMPONENTS serialization)

# Make a library
setup_library(module HexaBoard 
              dependencies Reformat::Reformat
                           Boost::serialization)

setup_python(package_name Reformat)
