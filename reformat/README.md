# reformat

Reformat raw data into a Framework EventFile.

This reformatting is not meant to decode any data, that is meant to be done downstream inside of ldmx-sw.
Instead, this set of programs is meant to be a starting point for future online event building.

## core
This is the module that is the main interface between different serialization schemes (Rogue, Boost.Serialization,...)
and the Framework EventFile. Look into it's README for defining a specific reformatting application.
