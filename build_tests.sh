#!/bin/sh

# Enable xtrace and errexit modes
set -xe

# Set the necessary paths
GTEST_DIR=/opt/homebrew/Cellar/googletest/1.14.0
GTEST_INCLUDE_DIR=${GTEST_DIR}/include
GTEST_LIB_DIR=${GTEST_DIR}/lib

# Source code directory
SRC_DIR="src"

# Header directory
HEADER_DIR="headers"

# Test directory
TEST_DIR="tests"

# Output directory
OUTPUT_DIR="bin"

# Output executable name
OUTPUT_EXECUTABLE="uc_tests"

# Compiler command
CC="g++ -std=c++20"

# Compilation options (CFLAGS)
CFLAGS="-Wall -Wextra -O2"

# Include paths for header files and Google Test
INCLUDE_PATH="-I$HEADER_DIR -I$GTEST_INCLUDE_DIR"

# Library path for Google Test
LIBRARY_PATH="-L$GTEST_LIB_DIR"

# Google Test libraries
GTEST_LIBS="-lgtest -lgtest_main -pthread"

# List of source files (excluding the main file)
SOURCE_FILES="$SRC_DIR/constants.cpp $SRC_DIR/conversions.cpp $SRC_DIR/utilities.cpp"

# Test files
TEST_FILES="$TEST_DIR/test_main.cpp"

# Create the output directory if it doesn't exist
mkdir -p $OUTPUT_DIR

# Compile and link the source files, test files, and Google Test libraries
$CC $CFLAGS $INCLUDE_PATH $LIBRARY_PATH $SOURCE_FILES $TEST_FILES $GTEST_LIBS -o $OUTPUT_DIR/$OUTPUT_EXECUTABLE
