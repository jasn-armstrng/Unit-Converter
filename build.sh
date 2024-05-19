#!/bin/sh

# Enable xtrace and errexit modes
set -xe

# Source code file name
SOURCE_FILE="src/main.cpp"

# Output executable name
OUTPUT_EXECUTABLE="bin/unitconv"

# Compiler command
CC="gcc -std=c++20"

# Compilation options (CFLAGS)
CFLAGS="-Wall -Wextra -O2"

# Compile the source code
$CC $SOURCE_FILE $CFLAGS -o $OUTPUT_EXECUTABLE
