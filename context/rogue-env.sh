#!/bin/bash

################################################################################
# rogue-env.sh
#   Set-up the Rogue environment inside the container
#   A lot of this has been copied manually from Rogue's setup_rogue.sh
#   script that is built when Rogue is compiled.
################################################################################

export ROGUE_DIR=/usr/local
export ROGUE_VERSION=v5.9.3

export PYTHONPATH=${PYTHONPATH:+:$PYTHONPATH}${ROGUE_DIR}/python
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}${ROGUE_DIR}/lib:${EPICS_BASE}/lib/linux-x86_64:${EPICS_PCAS_ROOT}/lib/linux-x86_64

# PYDM environment
export PYQTDESIGNERPATH=${ROGUE_DIR}/python/pyrogue/pydm:${PYQTDESIGNERPATH}
export PYDM_DATA_PLUGINS_PATH=${ROGUE_DIR}/python/pyrogue/pydm/data_plugins
export PYDM_TOOLS_PATH=${ROGUE_DIR}/python/pyrogue/pydm/tools

