# context
The DAQ software environment for LDMX.

While we aren't planning to actually use containers for our DAQ path,
having a container with the necessary software tools will help distribute
the environment to developers in the collaboration.

This docker file will also be a helpful guide to getting started on a new computer
because it lists all of the mandatory requirements for building and running these
software tools.

## Image

The image is built off of the [Rogue docker image](https://hub.docker.com/r/tidair/rogue).
I can't find good documentation on how this image is built, but it does have the most recent releases of Rogue.

On-top of the Rogue image, we have ROOT, Boost, and some Ubuntu packages ROOT requires.
Additionally, we put in our normal development-image entrypoint script so we can use this image like other dev images.

## Usage
With a similar entrypoint script as the base ldmx-sw development image,
the process for developing with this image is pretty similar.
The only difficult is that the repository this image resides in is not one of the canonical
repositories stored in the ldmx-env.sh script. Thus, we need to download and rename the image manually.

### docker
```bash
docker pull tomeichlersmith/daq-env:<version>
docker tag tomeichlersmith/daq-env:<version> ldmx/local:daq-env-<version>
```

### singularity
```bash
cd $LDMX_BASE
singularity build tomeichlersmith_daq-env_<version>.sif docker://tomeichlersmith/daq-env:<version>
ln -s tomeichlersmith_daq-env_<version>.sif ldmx_local_daq-env-<version>.sif
```

With this setup, you can then run
```bash
ldmx use local daq-env-<version>
```
to start developing with this container.
