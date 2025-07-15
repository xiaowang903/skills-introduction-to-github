#!/bin/bash

# Create build directory
mkdir -p build
cd build

# Build the plugin
qmake ../DeepSeekPlugin.pro
make

# Build the test application
cd ../TestApp
mkdir -p build
cd build
qmake ../TestApp.pro
make

echo "Build completed!"
echo "To run the test application, execute: ./TestApp/build/TestApp"