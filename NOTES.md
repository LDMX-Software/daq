
# Rogue DAQ

Rogue base docker image: github.com/slaclab/rogue-base-docker
Rogue central repo     : github.com/slaclab/rogue

Environment not perfectly setup in singularity, need to provide some extra lib paths:

```
export LD_LIBRARY_PATH=/usr/local/lib:${EPICS_BASE}/lib/linux-x86_64:${EPICS_PCAS_ROOT}/lib/linux-x86_64
```

Still unable to find PyQt5.

Could develop our DAQ path on top of Rogue image, 
probably with an intermediate image where we get the internal environment setup to align with our workflow.

## DAQ Path

Rogue allows for user defined data sources which can stream data to one or more destinations.
We can define a single Rogue-type source using different channels for our different 
which can forward the data on to a central stream.

HGC ROC 0 Link 0 --------| rogue channel 0 |
HGC ROC 0 Link 1 --------| rogue channel 1 |                   | -- event building
HGC ROC 1 Link 0 --------| rogue channel 2 |                   |
HGC ROC 1 Link 1 --------|                 |                   | -- rogue writer
  ...                    |                 |-- rogue source -- |
QIE Chip 0 --------------|    .........    |                   | -- dqm
QIE Chip 1 --------------|                 |
  ....                   |                 |
Other Chip Type ---------|                 |
