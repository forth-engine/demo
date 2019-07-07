
set(include_srcs
	common/birdview.h
	common/orbitview.h
	common/shaders.h
	common/utility.h
	common/time.h
)


if (EMSCRIPTEN)
	set(demo_libraries
		forth_static
		"-s USE_GLFW=3"
		"-s USE_WEBGL2=1"
		"-Os"
		"--preload-file ../../assets/@assets/"
		${ADDITIONAL_LIBRARIES}
	)
else()
	set(demo_libraries
		${OPENGL_LIBRARIES}
		forth_static
		${ADDITIONAL_LIBRARIES}
		GLEW_1130
		glfw
	)
endif()

add_executable( primitiveDemo primitive.cpp ${demo_srcs} )
add_executable( physicsDemo physics.cpp ${demo_srcs} )
add_executable( frustumDemo frustum.cpp ${demo_srcs} )
add_executable( thirdPersonViewDemo thirdPersonView.cpp ${demo_srcs} )
add_executable( particlesDemo particles.cpp ${demo_srcs} )
add_executable( directPipelineDemo directPipeline.cpp ${demo_srcs} )

target_link_libraries( primitiveDemo ${demo_libraries} )
target_link_libraries( physicsDemo ${demo_libraries} )
target_link_libraries( frustumDemo ${demo_libraries} )
target_link_libraries( thirdPersonViewDemo ${demo_libraries} )
target_link_libraries( particlesDemo ${demo_libraries} )
target_link_libraries( directPipelineDemo ${demo_libraries} )

if (EMSCRIPTEN)

	set_target_properties(primitiveDemo PROPERTIES SUFFIX ".html")
	set_target_properties(physicsDemo PROPERTIES SUFFIX ".html")
	set_target_properties(frustumDemo PROPERTIES SUFFIX ".html")
	set_target_properties(thirdPersonViewDemo PROPERTIES SUFFIX ".html")
	set_target_properties(particlesDemo PROPERTIES SUFFIX ".html")
	set_target_properties(directPipelineDemo PROPERTIES SUFFIX ".html")

else()

	file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

	set_property(TARGET primitiveDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set_property(TARGET physicsDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set_property(TARGET frustumDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set_property(TARGET thirdPersonViewDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set_property(TARGET directPipelineDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set_property(TARGET particlesDemo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

endif()
