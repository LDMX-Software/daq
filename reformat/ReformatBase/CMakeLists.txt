# Set the project name
project(ReformatBase)

setup_library(module ReformatBase
              dependencies Framework::Framework)

# Add the executable
add_executable(reformat ${PROJECT_SOURCE_DIR}/app/reformat.cxx)
target_link_libraries(reformat PUBLIC ReformatBase::ReformatBase)
install(TARGETS reformat
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
