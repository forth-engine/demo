#pragma once

// Standard includes appear here.......
// Include standard headers
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#endif

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// Include Forth
#include <forth.h>
using namespace Forth;

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

#define BIND_VA_VB(va, vb)     \
	glGenVertexArrays(1, &va); \
	glBindVertexArray(va);     \
	glGenBuffers(1, &vb);

#if __EMSCRIPTEN__
#define COMMON_SHADER "assets/vertexES.vs", "assets/fragmentES.fs"
#else
#define COMMON_SHADER "assets/vertex.vs", "assets/fragment.fs"
#endif

#define GL_RESET() glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

#define GL_SWAP(window)      \
	glfwSwapBuffers(window); \
	glfwPollEvents();

#if __EMSCRIPTEN__
#define MAIN_LOOP emscripten_set_main_loop(main_loop, 0, 0);
#else
#define MAIN_LOOP                                 \
	do                                            \
	{                                             \
		main_loop();                              \
	} while (glfwWindowShouldClose(window) == 0); \
	glfwTerminate();                              \
	return 0;
#endif

std::string GetAppPath()
{
#if __EMSCRIPTEN__
	return "";
#else
	char *cwd = _getcwd(0, 0); // **** microsoft specific ****
	std::string working_directory(cwd);
	std::free(cwd);
	return working_directory;
#endif
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, SCR_WIDTH = width, SCR_HEIGHT = height);
}

GLFWwindow *GlobalInit(const char *title, const char *help, GLFWcursorposfun mouse_callback = NULL, GLFWscrollfun scroll_callback = NULL, GLFWkeyfun key_callback = NULL, GLFWmousebuttonfun mouse_btn_callback = NULL)
{
	std::cout << title << std::endl;
	std::cout << help << std::endl;
	std::cout << "Loading...";

	// Initialise GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		std::cin.get();
		return NULL;
	}

	// Window contexts
	glfwWindowHint(GLFW_SAMPLES, 4);							   // Antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);				   // Target major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);				   // Target minor
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		   // MacOS specific
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);					   // Need resizable
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core Profile

	// Open a window and create its OpenGL context
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to open GLFW window. Requires OpenGL 3.3\n";
		std::cin.get();
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		std::cin.get();
		glfwTerminate();
		return NULL;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Standard callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_btn_callback);

	// VSync on
	glfwSwapInterval(1);

	// Enable depth test, fragment, culling
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_CULL_FACE);

	// White background
	glClearColor(1.f, 1.f, 1.0f, 0.0f);

	std::cout << "\rWindow Initialized\n";
	return window;
}