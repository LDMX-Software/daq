# Set the project name
project(ReformatBase)

find_package(Boost REQUIRED COMPONENTS python)

setup_library(module ReformatBase
              dependencies Framework::Framework
                           Boost::python)

setup_python(package_name Reformat)
