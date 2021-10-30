#!/bin/sh
g++ -Wall -Wextra main.cpp -o main.out `root-config --cflags --libs`
./main.out
