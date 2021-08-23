#!/bin/bash

###############################################################################
# common.sh
#   Shared bash functions between many different actions.
#
#   Assumptions
#     - The env variable LDMX_DOCKER_TAG has the image we should be using
#     - The repo has been checked out using actions/checkout@v2
#       OR the build package was unpacked to mimic this effect
#       (this assumption basically means that GITHUB_WORKSPACE points to the repo)
#
#   Usage
#     GitHub defines GITHUB_ACTION_PATH to be the full path to the diretory
#     for the action that is being run. This means, since this file is one
#     below that directory, we can source it like so
#       source ${GITHUB_ACTION_PATH}/../common.sh
#     https://docs.github.com/en/actions/reference/environment-variables
###############################################################################

# container running command
#   - Assume LDMX_DOCKER_TAG is the image we run in
#   - Full command needs to be provided
#   - Runs inside the present working directory
ldmx() {
  docker run \
    -i -v ${LDMX_BASE}:${LDMX_BASE} -e LDMX_BASE \
    -u $(id -u $USER):$(id -g $USER) \
    ${LDMX_DOCKER_TAG} $(pwd) $@
  return $?
}

# GitHub workflow command to set an output key,val pair
set_output() {
  local _key="$1"
  local _val="$2"
  echo "${_key} = ${_val}"
  echo "::set-output name=${_key}::${_val}"
}

# GitHub workflow command to start an group of output messages
start_group() {
  echo "::group::$@"
}

# GitHub workflow command to end previously started group
end_group() {
  echo "::endgroup::"
}

# GitHub workflow command to flag message as an error
error() {
  echo "::error::$@"
}

start_group Deduce Common Environment Variables
export LDMX_BASE=$(cd ${GITHUB_WORKSPACE}/../ && pwd)
echo "LDMX_BASE=${LDMX_BASE}"
end_group

