cmake_minimum_required(VERSION 3.10)
project(Advanced-CPP)

# Set common options
include(common.cmake)

# Add subdirectories for each module
add_subdirectory(modules/01_Templates)
add_subdirectory(modules/02_STL)
add_subdirectory(modules/03_Memory)

create_executable_from_source("advanced_cpp_examples" modules/advanced_cpp_examples.cpp)
