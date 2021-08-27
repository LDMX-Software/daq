
FROM ubuntu:20.04
LABEL ubuntu.version="20.04"
MAINTAINER Tom Eichlersmith <eichl008@umn.edu>

# First install any required dependencies from ubuntu repos
RUN apt-get update &&\
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y \
        binutils \
        ca-certificates \
        cmake \
        fonts-freefont-ttf \
        g++-7 \
        gcc-7 \
        libboost-all-dev \
        libbz2-dev \
        libfftw3-dev \
        libfreetype6-dev \
        libftgl-dev \
        libgif-dev \
        libgl1-mesa-dev \
        libgl2ps-dev \
        libglew-dev \
        libglu-dev \
        libjpeg-dev \
        liblz4-dev \
        liblzma-dev \
        libpcre++-dev \
        libpng-dev \
        libreadline6-dev \
        libssl-dev \
        libx11-dev \
        libxext-dev \  
        libxft-dev \
        libxml2-dev \
        libxmu-dev \
        libxpm-dev \
        libz-dev \
        libzmq3-dev \
        libzstd-dev \
        locales \
        make \
        python3-dev \
        python3-pip \
        python3-numpy \
        python3-tk \
        python3-pyqt5 \
        srm-ifce-dev \
        wget \
    && rm -rf /var/lib/apt/lists/* &&\
    apt-get autoremove --purge &&\
    apt-get clean all

###############################################################################
# Source-Code Downloading Method
#   mkdir src && ${__wget} <url-to-tar.gz-source-archive> | ${__untar}
#
#   Adapted from acts-project/machines
###############################################################################
ENV __wget wget -q -O -
ENV __untar tar -xz --strip-components=1 --directory src
ENV __prefix /usr/local

# All init scripts in this directory will be run upon entry into container
ENV __ldmx_env_script_d__ /etc/ldmx-container-env.d
RUN mkdir ${__ldmx_env_script_d__}

#run environment setup when docker container is launched and decide what to do from there
#   will require the environment variable LDMX_BASE defined
COPY ./entry.sh /etc/
RUN chmod 755 /etc/entry.sh
ENTRYPOINT ["/etc/entry.sh"]

###############################################################################
# CERN's ROOT
###############################################################################
LABEL root.version="6.22.08"
RUN mkdir src &&\
    ${__wget} https://root.cern/download/root_v6.22.08.source.tar.gz |\
     ${__untar} &&\
    cmake \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_STANDARD=17 \
      -DCMAKE_INSTALL_PREFIX=${__prefix} \
      -Dgminimal=ON \
      -Dgdml=ON \
      -Dopengl=ON \
      -Dpyroot=ON \
      -Dgnuinstall=ON \
      -Dxrootd=OFF \
      -B build \
      -S src \
    && cmake --build build --target install &&\
    ln -s /usr/local/bin/thisroot.sh ${__ldmx_env_script_d__}/thisroot.sh &&\
    rm -rf build src

###############################################################################
# EPICS 
#   - setup_rogue.sh requires the EPICS_BASE env variable defined
###############################################################################
LABEL epics.version="v7.0.3"
RUN mkdir src &&\
    ${__wget} https://github.com/epics-base/epics-base/archive/R7.0.3.tar.gz |\
      ${__untar} &&\
    cd src &&\
    make INSTALL_LOCATION=${__prefix} &&\
    cd .. && rm -rf src
ENV EPICS_BASE ${__prefix}

###############################################################################
# PCAS
#   - setup_rogue.sh requires the EPICS_PCAS_ROOT env variable defined
###############################################################################
LABEL pcas.version="v4.13.2"
RUN mkdir src &&\
    ${__wget} https://github.com/epics-modules/pcas/archive/v4.13.2.tar.gz |\
      ${__untar} &&\
    cd src &&\
    make INSTALL_LOCATION=$EPICS_BASE/pcas EPICS_BASE=$EPICS_BASE &&\
    cd .. && rm -rf src
ENV EPICS_PCAS_ROOT $EPICS_BASE/pcas

###############################################################################
# Rogue Helper Python Packages
###############################################################################
RUN python3 -m pip install --no-cache-dir \ 
      PyYAML \
      Pyro4 \
      parse \
      click \
      ipython \
      pyzmq \
      packaging \
      matplotlib \
      numpy \
      pyepics \
      p4p \
      pydm \
      jsonpickle \
      sqlalchemy \
      pyserial

###############################################################################
# Rogue
###############################################################################
#LABEL rogue.version="v5.9.3"
#ENV LD_LIBRARY_PATH /usr/local/lib:/usr/local/pcas/lib
#RUN mkdir src &&\
#    ${__wget} https://github.com/slaclab/rogue/archive/refs/tags/v5.9.3.tar.gz |\
#      ${__untar} &&\
#    cmake \
#      -B src/build \
#      -S src \
#      -DROGUE_INSTALL=system \
#      -DROGUE_VERSION=v5.9.3 \
#      -DCMAKE_INSTALL_PREFIX=${__prefix} &&\
#    cmake --build src/build --target install &&\
#    rm -r src
#COPY ./rogue-env.sh ${__ldmx_env_script_d__}/
