# Set the project name
project(ReformatBase)

find_package(Boost REQUIRED COMPONENTS python)

setup_library(module ReformatBase
              dependencies Framework::Framework
                           Boost::python)
