#!/bin/sh

# Enable xtrace and errexit modes
set -xe

# Source code directory
SRC_DIR="src"

# Header directory
HEADER_DIR="headers"

# Output directory
OUTPUT_DIR="bin"

# Output executable name
OUTPUT_EXECUTABLE="uc"

# Compiler command
CC="g++ -std=c++20"

# Compilation options (CFLAGS)
CFLAGS="-Wall -Wextra -O2"

# Include path for header files
INCLUDE_PATH="-I$HEADER_DIR"

# List of source files
SOURCE_FILES="$SRC_DIR/main.cpp"

# Create the output directory if it doesn't exist
mkdir -p $OUTPUT_DIR

# Compile and link the source files
$CC $CFLAGS $INCLUDE_PATH $SOURCE_FILES -o $OUTPUT_DIR/$OUTPUT_EXECUTABLE
