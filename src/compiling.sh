#!/bin/sh
g++ -Wall -Wextra -o program.out ParticleType.cpp ResonanceType.cpp Particle.cpp main.cpp `root-config --cflags --libs`
