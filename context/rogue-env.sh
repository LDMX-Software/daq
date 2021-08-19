#!/bin/bash

################################################################################
# rogue-env.sh
#   Set-up the Rogue environment inside the container
################################################################################

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}/usr/local/lib:${EPICS_BASE}/lib/linux-x86_64:${EPICS_PCAS_ROOT}/lib/linux-x86_64
