#pragma once

// Standard includes appear here.......
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif
#include <unistd.h>
#endif
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// Include Forth
#include <forth.h>
using namespace Forth;

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

#define CREATE_AND_BIND_VA(va) \
	GLuint va; \
	glGenVertexArrays(1, &va);\
	glBindVertexArray(va);

#define CREATE_VB(vb) \
	GLuint vb; \
	glGenBuffers(1, &vb);

#define GL_CLRSRC() glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

#define GL_SWAP(window) glfwSwapBuffers(window); glfwPollEvents();


std::string GetAppPath() {
	char* cwd = _getcwd(0, 0); // **** microsoft specific ****
	std::string working_directory(cwd);
	std::free(cwd);
	return working_directory;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, SCR_WIDTH = width, SCR_HEIGHT = height);
}

GLFWwindow* GlobalInit (const char* title, const char* help, GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback, GLFWkeyfun key_callback)
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
	glfwWindowHint(GLFW_SAMPLES, 4); // Antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Target major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Target minor
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS specific
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // Need resizable
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core Profile

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
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

	// VSync on
	glfwSwapInterval(1);

	// Enable depth test, fragment, culling
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);

	// White background
	glClearColor(1.f, 1.f, 1.0f, 0.0f);

	std::cout << "\rWindow Initialized\n";
	return window;
}