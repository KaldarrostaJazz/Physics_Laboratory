# Particle collider simulator.
This is a simulation of a particle collision esperiment, such as the ones performed at CERN's ALICE, generated using Montecarlo generation integrated in ROOT. I 
will add more details in the future. This code is part of my physics laboratory exam at University of Bologna.

--------------------------------------------------------------------------------

## Dependencies
- [ROOT](https://root.cern/) (required, version 6.18^)
- [Doctest](https://github.com/onqtam/doctest) (bundled)

## Building
You can either build this program via terminal or inside ROOT.
Note that in both cases, a folder named ```pdfs``` and a folder named ```rootfiles``` must exixt your directory. Otherwise the program won't print the histograms.

### Building via terminal (bash)
To compile the code, go into ```src/``` folder:
```shell
g++ -o program.out ParticleType.cpp ResonanceType.cpp Particle.cpp main.cpp `root-config --cflags --libs`
```
You can use whatever c++ compiler you prefer.

To run the program:
```shell
./program.out
```

Since the command is too long and boring, I also created a ```.sh``` file that executes it for you. Just do:
```shell
bash compiling.sh
```
Please note that in the ```.sh``` file warnings are enabled.

A warning signaling a declared but unused variable should appear:
```shell
Particle.cpp: In member function ‘int Particle::decayTo(Particle&, Particle&) const’:
Particle.cpp:31:11: warning: variable ‘y2’ set but not used [-Wunused-but-set-variable]
   31 |     float y2;
      |           ^~o build 
```
### Building via ROOT
The preferred way to build this code is inside ROOT.

In ```src/``` run ROOT, then:
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
This method is preferred because it tooks less time. However, compiling this way will generate new files, wich are the dynamic libraries needed by ROOT to run 
the program. Don't panic if you see appearing ```.so```, ```.d``` and ```.pcm``` files.

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
