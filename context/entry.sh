#!/bin/bash 

set -e

###############################################################################
# Entry point for the ldmx development container
#   The basic idea is that we want to go into the container,
#   setup the ldmx-sw working environment, and then
#   run whatever executable the user wants.
#
#   A lot of executables require us to be in a specific location,
#   so the first argument is required to be a directory we can go to.
#   The rest of the arguments are passed to `eval` to be run as one command.
#
#   All of the aliases that are defined in the ldmx-env script will
#   have $(pwd) be the first argument to the entrypoint.
#   This means, before executing anything on the container,
#   we will go to the mounted location that the user is running from.
#
#   Assumptions:
#   - The installation location of daq/reformat is defined in REFORMAT_INSTALL
#     or it is located at LDMX_BASE/daq/reformat/install
#   - Any initialization scripts for external dependencies need to be
#     symlinked into the directory ${__ldmx_env_script_d__}
###############################################################################

# Set-up computing environment
# WARNING: No check to see if there is anything in this directory
for init_script in ${__ldmx_env_script_d__}/*; do
  . $(realpath ${init_script})
done
unset init_script

# add ldmx-sw and ldmx-analysis installs to the various paths
if [ -z "${REFORMAT_INSTALL}" ]; then
  export REFORMAT_INSTALL=$LDMX_BASE/daq/reformat/install
fi
export LD_LIBRARY_PATH=$REFORMAT_INSTALL/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$REFORMAT_INSTALL/python:$PYTHONPATH
export PATH=$REFORMAT_INSTALL/bin:$PATH

# helps simplify any cmake nonsense
export CMAKE_PREFIX_PATH=/usr/local/lib:$REFORMAT_INSTALL

# go to first argument
cd "$1"

# execute the rest as a one-liner command
eval "${@:2}"
