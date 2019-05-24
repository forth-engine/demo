
set(demo_srcs
	main.cpp
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
