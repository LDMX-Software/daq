# MyModule

Example custom module for work with Rogue.

The basic idea of a custom Rogue module is two-tiered.

1. C++ implementations of custom sources/destinations for data.
  - These custom classes are then bound to python using Boost.Python 
    and some infrastructure set-up by the parent Rogue library.
  - The output library is stripped of the 'lib' prefix so that
    `import MyModule` can be used.
  - This is roughly similar to how the `rogue` python module is built
2. Python wrappers to make interfacing with the custom C++ easier.
  - These wrappers are housed in the `MyWrapper` module so that
    the wrapping Python classes can have the same names as the C++-bound
    underlying classes without leading to conflicts.
  - This is roughly similar to how the `pyrogue` python module is built

