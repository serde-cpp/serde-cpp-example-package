cmake_minimum_required(VERSION 3.5)
project(example LANGUAGES CXX)

#########################################################################################
# Configuration
#########################################################################################
# Default build type to Debug, for release use `cmake -DCMAKE_BUILD_TYPE=Release ..`
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type default to Debug" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Turn on when having trouble building
set(CMAKE_VERBOSE_MAKEFILE OFF)
# Compilation Database for C++ language servers
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default compilation settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -pg -fsanitize=undefined -Wall -Wno-attributes")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -Wall -Wno-attributes")

#########################################################################################
# Dependencies
#########################################################################################
find_package(serde_cpp REQUIRED)
find_package(ryml REQUIRED)

#########################################################################################
# Project
#########################################################################################
# Generate Serde files
serde_generate(example_serde
  src/main.cpp      # output: ${CMAKE_BINARY_DIR}/src/main_serde.h
)
# Build project executable
add_executable(example
  src/main.cpp
)
target_link_libraries(example PRIVATE
  example_serde
  serde_cpp::serde
  serde_cpp::serde_yaml
  ryml::ryml
)
