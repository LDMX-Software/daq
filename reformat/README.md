# reformat

Reformat raw data into a Framework EventFile.

This reformatting is not meant to decode any data, that is meant to be done downstream inside of ldmx-sw.
Instead, this set of programs is meant to be a starting point for future online event building.

## Building
I assume that the user is using the image built by the context defined in the [context directory](context).
Since this image is stored in a repository that is not one of the canonical repositories defined in the env script,
we need to download the image manually.
```bash
docker pull tomeichlersmith/daq-env:latest
docker tag tomeichlersmith/daq-env:latest ldmx/local:daq-env
```
Then you can start using the environment commands.
```bash
ldmx use local daq-env
```

Building this software is similar to ldmx-sw.
```bash
cd reformat
mkdir build
cd build
ldmx cmake ..
ldmx make install
```

## Table of Contents

### Framework
The Framework module from ldmx-sw.

### cmake
Common cmake macros used in LDMX-Software.

### ReformatBase
This is the module that is the main interface between different serialization schemes (Rogue, Boost.Serialization,...)
and the Framework EventFile.

### hexaboard
A band-aid solution for converting the Boost.Serialization output of hexactrl-sw.
