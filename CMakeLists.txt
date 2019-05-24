# CMakeList.txt : CMake project for Forth-Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)

# Add source to this project's executable.
project (ForthEngineDemo CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

find_package(OpenGL REQUIRED)

add_subdirectory (extern)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${forth_SOURCE_DIR}/include
	extern/glfw/include/
	extern/glew/include/
	extern/glew/lib/
	extern/glm/
	.
)

add_subdirectory(source)

# TODO: Add tests and install targets if needed.
