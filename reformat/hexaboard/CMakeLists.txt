# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(
  hexaboard
  VERSION 1.0.0
  DESCRIPTION "Translation layer between hexactrl-sw and ldmx-sw."
  LANGUAGES CXX)

# Search for Boost
find_package(
  Boost REQUIRED
  COMPONENTS serialization
             program_options)

# Make a library
setup_library(module hexaboard dependencies Framework::Framework)
              
# Add the executable
add_executable(hexa-reformat ${PROJECT_SOURCE_DIR}/src/hexa_reformat.cxx)
target_link_libraries(hexa-reformat 
                      PUBLIC hexaboard::hexaboard
                             Boost::program_options)
install(TARGETS hexa-reformat
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

