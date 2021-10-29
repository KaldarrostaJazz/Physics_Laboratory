#!/bin/sh
g++ -Wall -Wextra main.cpp -o analysis.out `root-config --cflags --libs`
./analysis.out
