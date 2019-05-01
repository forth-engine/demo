# CMakeList.txt : CMake project for Forth-Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)

# Add source to this project's executable.
project (Forth-Engine-Demo)
add_subdirectory(extern)
add_subdirectory(source)

# TODO: Add tests and install targets if needed.
