# daq
**D**ata **Aq**uisition

This repository is focused on the software tools necessary to collect data coming off of the LDMX detector.

<a href="http://perso.crans.org/besson/LICENSE.html" alt="GPLv3 license">
    <img src="https://img.shields.io/badge/License-GPLv3-blue.svg" />
</a>

## Table of Contents

### context
<a href="https://github.com/LDMX-Software/daq/actions/workflows/build_context.yml" alt="Actions">
    <img src="https://github.com/LDMX-Software/daq/actions/workflows/build_context.yml/badge.svg" />
</a>
<a href="https://hub.docker.com/repository/docker/tomeichlersmith/daq-env" alt="DockerHub">
    <img src="https://img.shields.io/docker/v/tomeichlersmith/daq-env/latest" />
</a>

This is the docker build context for a development environment container.
**It is not assumed that the actual DAQ will be done from within a container**; however,
this enables any collaborator who has docker or singularity installed to contribute.

This also is a very direct way of documenting how the dependencies are installed on a new system.

### online
Our [Rogue](https://slaclab.github.io/rogue/interfaces/index.html) application that is launched to collect and stream data.
This software is deeply tied to the firmware that will be on our front-end hardware, 
so it is being held in a separate repository [slaclab/ldmx-daq](github.com/slaclab/ldmx-daq) which is private.

### reformat
<a href="https://github.com/LDMX-Software/daq/actions/workflows/reformat_test.yml" alt="Actions">
    <img src="https://github.com/LDMX-Software/daq/actions/workflows/reformat_test.yml/badge.svg" />
</a>

The short preparation timeline forced us to create a stop-gap measure to insure ourselves against data loss due to bugs in quickly developed software.
For this reason, the online data output will be simply a binary file written by [Rogue's native writer](https://slaclab.github.io/rogue/utilities/fileio/writing.html) and 
then this directory contains a program to reformat this data by aligning it into events and putting it into the Framework's EventFile format.
