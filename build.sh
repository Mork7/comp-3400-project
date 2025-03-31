#!/bin/bash

# Set colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Starting build process...${NC}"

# Navigate to project directory
cd "$(dirname "$0")"
PROJECT_DIR=$(pwd)
echo -e "${GREEN}Project directory: ${PROJECT_DIR}${NC}"

# Remove build directory if it exists
if [ -d "build" ]; then
    echo -e "${YELLOW}Removing existing build directory...${NC}"
    rm -rf build
fi

# Create build directory
echo -e "${YELLOW}Creating new build directory...${NC}"
mkdir -p build
cd build

# Run cmake
echo -e "${YELLOW}Running CMake...${NC}"
cmake .. || { echo -e "${RED}CMake configuration failed!${NC}"; exit 1; }

# Run make
echo -e "${YELLOW}Building project...${NC}"
make || { echo -e "${RED}Build failed!${NC}"; exit 1; }

echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${YELLOW}Run your application with: ${GREEN}./build/hospital_system${NC}"