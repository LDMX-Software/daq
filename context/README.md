# context
The DAQ software environment for LDMX.

While we aren't planning to actually use containers for our DAQ path,
having a container with the necessary software tools will help distribute
the environment to developers in the collaboration.

## Image

The image is built off of the [Rogue docker image](https://hub.docker.com/r/tidair/rogue).
I can't find good documentation on how this image is built, but it does have the most recent releases of Rogue.

On-top of the Rogue image, we have ROOT, Boost, and some Ubuntu packages ROOT requires.
Additionally, we put in our normal development-image entrypoint script so we can use this image like other dev images.
