# Source for CMakeLists.txt

# Add support for building in conda environment
if (DEFINED ENV{CONDA_PREFIX})
  set(CMAKE_PREFIX_PATH "$ENV{CONDA_PREFIX}")
  link_directories($ENV{CONDA_PREFIX}/lib)
endif()

# Check cmake version
cmake_minimum_required(VERSION 3.5)
include(InstallRequiredSystemLibraries)

# Project name, Replace with your name
project (MyModule)

# C/C++
enable_language(CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wno-deprecated")

#####################################
# Find Rogue & Support Libraries
#####################################
if (DEFINED ENV{ROGUE_DIR})
  set(Rogue_DIR $ENV{ROGUE_DIR}/lib)
else()
  set(Rogue_DIR ${CMAKE_PREFIX_PATH}/lib)
endif()
find_package(Rogue)

#####################################
# Setup build
#####################################

# Include files
include_directories(${ROGUE_INCLUDE_DIRS})

# Create rogue python library, point to your source file
add_library(MyModule SHARED MyModule.cpp)

# Set output to TOP/lib, remove lib prefix
set_target_properties(MyModule PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/python)
set_target_properties(MyModule PROPERTIES PREFIX "")

# Link to rogue core
target_link_libraries(MyModule PUBLIC ${ROGUE_LIBRARIES})
