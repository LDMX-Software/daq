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
              
# Add the executable
add_executable(hexa-reformat ${PROJECT_SOURCE_DIR}/src/HexaBoard/hexa_reformat.cxx)
target_link_libraries(hexa-reformat 
                      PUBLIC HexaBoard::HexaBoard
                             Boost::program_options)
install(TARGETS hexa-reformat
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
