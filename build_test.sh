#!/bin/sh

# Enable xtrace and errexit modes
set -xe

# Set the necessary paths
GTEST_DIR=/opt/homebrew/Cellar/googletest/1.14.0
GTEST_INCLUDE_DIR=${GTEST_DIR}/include
GTEST_LIB_DIR=${GTEST_DIR}/lib

# Source files
TEST_FILES="tests/test_main.cpp"

# Output executable
OUTPUT_DIR="bin"
OUTPUT_EXECUTABLE="${OUTPUT_DIR}/guc_tests"

# Compile the test files and link with the Google Test lib
g++ -std=c++20 -I${GTEST_INCLUDE_DIR} -L${GTEST_LIB_DIR} ${TEST_FILES} -lgtest -lgtest_main -pthread -o ${OUTPUT_EXECUTABLE}
