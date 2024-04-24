#!/bin/bash

# Compile and generate separate executables for different optimization levels

# Clean up previous builds
rm -rf build
mkdir build
cd build || exit

# Compile with different optimization levels
clang -O0 -o O0 ../src/quicksort.c
clang -O1 -o O1 ../src/quicksort.c
clang -O2 -o O2 ../src/quicksort.c
clang -O3 -o O3 ../src/quicksort.c
clang -Ofast -o Ofast ../src/quicksort.c
clang -Oz -o Oz ../src/quicksort.c
