#!/bin/sh
g++ -Wall -Wextra main.cpp -o main.out `root-config --cflags --libs`
echo COMPILED WITH SUCCESS!
echo ----------------------
echo NOW RUNNING THE EXE
./main.out
