
set(demo_srcs
	main.cpp
	common/shaders.h
	common/camera.h
)

add_executable(
	demo
	${demo_srcs}
)

target_link_libraries(
	demo
	${OPENGL_LIBRARIES}
	GLEW_1130
	glfw
	forth_static
	${ADDITIONAL_LIBRARIES}
)

file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)
