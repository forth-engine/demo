#pragma once

#include "utility.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace Forth;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class OrbitView
{

	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouse = true;

  public:
	// Euler Angles
	float lon;
	float lat;
	float azm;
	// Camera options
	float speed;
	vec3 position;
	float zoom;

	// Constructor with vectors
	OrbitView()
	{
		lon = 0;
		lat = 0;
		azm = 0;
		speed = 2.0;
		position = vec3(0,0,-10.0f);
		zoom = 45.f;
	}

	glm::vec3 GetPosition3D()
	{
		return position;
	}

	glm::mat4 Get3DViewMatrix()
	{
		return glm::lookAt(GetPosition3D(),  glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

	glm::mat4 Get3DProjectionMatrix()
	{
		return glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	}

	Transform4 Get4DViewMatrix()
	{
		Matrix4 r = Forth::Euler(0, lat) * Forth::Euler(1, lon) * Forth::Euler(5, azm);
		return Transform4(Vector4::zero, r);
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(bool ctrl, float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= speed;
		yoffset *= speed;

		if (!ctrl)
		{
			lon += xoffset;
			lat += yoffset;
		}
		else
		{
			azm += xoffset;
		}

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			lat = Clamp(-89.f, 89.f, lat);
			azm = Clamp(-89.f, 89.f, azm);
		}
	}

	void ProcessGLFWMouse(GLFWwindow* window, float xpos, float ypos)
	{
		float Xpos = (float)xpos;
		float Ypos = (float)ypos;

		if (firstMouse)
		{
			lastX = Xpos;
			lastY = Ypos;
			firstMouse = false;
		}

		float xoffset = lastX - Xpos; // reserved to follow orbit logic
		float yoffset = lastY - Ypos; // reversed since y-coordinates go from bottom to top

		lastX = Xpos;
		lastY = Ypos;

		bool ctrl = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
		ProcessMouseMovement(ctrl, xoffset, yoffset);
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}
};