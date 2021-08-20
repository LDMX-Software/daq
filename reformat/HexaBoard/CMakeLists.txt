# Set the project name
project(HexaBoard)

# Search for Boost
find_package(
  Boost REQUIRED
  COMPONENTS serialization
             program_options)

# Make a library
setup_library(module HexaBoard 
              dependencies ReformatBase::ReformatBase
                           Boost::serialization)

setup_python(package_name Reformat/HexaBoard)
