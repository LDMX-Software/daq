# reformat

Reformat raw data into a Framework EventFile.

This reformatting is not meant to decode any data, that is meant to be done downstream inside of ldmx-sw.
Instead, this set of modules is meant to be a starting point for future online event building.

## Building
I assume that the user is using the image built by the context defined in the [context directory](./../context).
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

## Usage
This code-base is designed very similarly to the core Framework.
The `reformat` program is configured using a python script at run-time,
and the different input files can be dynamically loaded.
On-going notes and documentation can be seen in the [usage](usage.md) document.

## Table of Contents

### Framework
The Framework module from ldmx-sw.

### cmake
Common cmake macros used in LDMX-Software.

### Reformat
This is the module that is the main interface between different serialization schemes (Rogue, Boost.Serialization,...)
and the Framework EventFile.

### HexaBoard
A band-aid solution for converting the Boost.Serialization output of hexactrl-sw.

### Rogue
Reading from a Rogue-written binary file.
