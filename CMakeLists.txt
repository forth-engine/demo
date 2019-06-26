# CMakeList.txt : CMake project for Forth-Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)

# Add source to this project's executable.
project (ForthEngineDemo LANGUAGES C CXX)

if (MSVC)
	message(STATUS "MSVC")
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

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

if (EMSCRIPTEN)
	include_directories(
		${X11_X11_INCLUDE_PATH}
		${forth_SOURCE_DIR}/include/
		extern/glm/
		.
	)
else()
	include_directories(
		${OPENGL_INCLUDE_DIR}
		${forth_SOURCE_DIR}/include/
		extern/glfw/include/
		extern/glew/include/
		extern/glew/lib/
		extern/glm/
		.
	)
endif()

add_subdirectory(source)

# TODO: Add tests and install targets if needed.
