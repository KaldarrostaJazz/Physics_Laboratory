# Particle collision simulation.
This is a simulation of a particle collision esperiment, such as the ones performed at CERN's ALICE, generated using Montecarlo generation integrated in ROOT. I will add more details in the future.
This code is part of my physics laboratory exam at University of Bologna.

--------------------------------------------------------------------------------

## Dependencies
- [ROOT](https://root.cern/) (required, version 6.18^)
- [Doctest](https://github.com/onqtam/doctest) (bundled)

## Building
The preferred way to build this code is inside ROOT.
In src/ run root, then:
```shell
.L ParticleType.cpp+
.L ResonanceType.cpp+
.L Particle.cpp+
.L main.cpp+
```
Then, run :
```shell
main()
```
### Testing
Make sure to compile tests
```shell
g++ test.cpp -o test.out
```
then run:
```shell
./test.out
```

--------------------------------------------------------------------------------
