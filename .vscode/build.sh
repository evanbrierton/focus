#! /bin/bash

# Create a build folder if it doesn't exist
mkdir -p build

# Change the current directory to "build"
cd build || exit

# Create all the build files needed
cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ..

# Build
make

# Execute
./src/focus < testcase.txt