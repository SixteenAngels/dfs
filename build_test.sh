#!/bin/bash

echo "Building DFS Compression Library..."
echo

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. || {
    echo "CMake not found. Trying to compile manually..."
    cd ..
    exit 1
}

# Build the project
echo "Building project..."
cmake --build . || {
    echo "Build failed!"
    cd ..
    exit 1
}

# Run test if available
if [ -f test_dfs ]; then
    echo
    echo "Running test..."
    ./test_dfs
fi

cd ..
echo
echo "Build process completed."

