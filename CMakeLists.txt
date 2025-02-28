cmake_minimum_required(VERSION 3.10)
project(HospitalManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build directory
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Include directory
include_directories(include)

# Find all source files in src/
file(GLOB SRCS "src/*.cpp")

# Set output executable
add_executable(hospital_system ${SRCS})

# Set compiler flags
if (MSVC)
    target_compile_options(hospital_system PRIVATE /W4 /Zi) # Warning level 4 and debugging symbols for MSVC
else()
    target_compile_options(hospital_system PRIVATE -Wall -g) # Enable warnings and debugging for GCC/Clang
endif()
