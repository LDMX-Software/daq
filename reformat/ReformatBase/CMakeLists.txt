# Set the project name
project(ReformatBase)

setup_library(module ReformatBase
              dependencies Framework::Framework)

execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "CPYY_MODULE_PATH: " ${CPPYY_MODULE_PATH})
list(INSERT CMAKE_MODULE_PATH 0 ${CPPYY_MODULE_PATH})
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

find_package(Cppyy REQUIRED)

cppyy_add_bindings("Reformat"
  "v1.0.0"
  "Tom Eichlersmith" "eichl008@umn.edu"
  LANGUAGE_STANDARD 17
  H_DIRS ${PROJECT_SOURCE_DIR}/include/ReformatBase
  H_FILES "RawDataFile.h;Converter.h"
  INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
  LINK_LIBRARIES ReformatBase::ReformatBase)

