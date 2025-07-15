#!/bin/bash

# Create build directory
mkdir -p build
cd build

# Build the example
qmake ../SimpleExample.pro
make

echo "Build completed!"
echo "To run the example, execute: ./SimpleExample"