

### FORTH ###

add_subdirectory (forth)

### GLFW ###

if (EMSCRIPTEN)
else()
# Don't waste our time
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "BUILD GLFW Examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "BUILD GLFW Examples" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)

mark_as_advanced(FORCE GLFW_BUILD_EXAMPLES)
mark_as_advanced(FORCE GLFW_BUILD_TESTS)
mark_as_advanced(FORCE GLFW_BUILD_DOCS)
mark_as_advanced(FORCE GLFW_DOCUMENT_INTERNALS)

add_subdirectory (glfw)

include_directories(
	glfw/include/GLFW/
	glew/include/
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
	glew/src/glew.c
)

set(GLEW_HEADERS
	glew/include/GL/glew.h
)


add_library(GLEW_1130 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
	${GLEW_HEADERS}
)

target_link_libraries(GLEW_1130
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)
endif()