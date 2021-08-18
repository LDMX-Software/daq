# daq
**D**ata **Aq**uisition

This repository is focused on the software tools necessary to collect data coming off of the LDMX detector.

## Table of Contents

### context
This is the docker build context for a development environment container.
It is not assumed that the actual DAQ will be done from within a container; however,
this enables any collaborator who has docker or singularity installed to contribute.

### rogue
Our [Rogue](https://slaclab.github.io/rogue/interfaces/index.html) application that is launched to collect and stream the data.

### reformat
The short preparation timeline forced us to create a stop-gap measure to insure ourselves against data loss due to bugs in quickly developed software.
For this reason, the online data output will be simply a binary file written by [Rogue's native writer](https://slaclab.github.io/rogue/utilities/fileio/writing.html) and 
then this directory contains a program to reformat this data by aligning it into events and putting it into the Framework's EventFile format.
