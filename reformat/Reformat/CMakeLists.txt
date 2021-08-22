# Set the project name
project(Reformat)

find_package(Boost REQUIRED COMPONENTS python)

setup_library(module Reformat
              dependencies Framework::Framework
                           Boost::python)

setup_python(package_name Reformat)

add_executable(reformat ${PROJECT_SOURCE_DIR}/app/reformat.cxx)
target_link_libraries(reformat PRIVATE Reformat::Reformat)
install(TARGETS reformat DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
