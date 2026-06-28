#!/usr/bin/env bash

cd ../..
make clean
make FILE=optimization/code_vs_zombies/src/main.c
gcc -Wall -Wextra -o main codingame.c -lm
cd -
../../main < $1
