# Set the project name
project(reformat)

# Add the executable
add_executable(reformat reformat.cxx)
target_link_libraries(reformat PRIVATE Framework::Framework)
install(TARGETS reformat DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

