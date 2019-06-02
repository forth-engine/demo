
set(include_srcs
	common/birdview.h
	common/orbitview.h
	common/shaders.h
	common/utility.h
	common/time.h
)

set(demo_libraries
	${OPENGL_LIBRARIES}
	GLEW_1130
	glfw
	forth_static
	${ADDITIONAL_LIBRARIES}
)

# Demo 1

add_executable(
	primitiveDemo
	primitive.cpp
	${demo_srcs}
)

target_link_libraries(
	primitiveDemo
	${demo_libraries}
)

# Demo 2

add_executable(
	physicsDemo
	physics.cpp
	${demo_srcs}
)

target_link_libraries(
	physicsDemo
	${demo_libraries}
)

# Demo 3

add_executable(
	frustumDemo
	frustum.cpp
	${demo_srcs}
)

target_link_libraries(
	frustumDemo
	${demo_libraries}
)

# Demo 4

add_executable(
	directPipelineDemo
	directPipeline.cpp
	${demo_srcs}
)

target_link_libraries(
	directPipelineDemo
	${demo_libraries}
)

# Demo 5

add_executable(
	particlesDemo
	particles.cpp
	${demo_srcs}
)

target_link_libraries(
	particlesDemo
	${demo_libraries}
)

file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

set_property(TARGET primitiveDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(TARGET physicsDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(TARGET frustumDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(TARGET directPipelineDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(TARGET particlesDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
