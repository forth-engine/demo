// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// Include Forth
#include "common/camera.h"
#include "common/shaders.h"
#include <forth.h>
#include <fstream>

// Classes necessary for rendering
Forth::Model4 tesseract = Forth::Model4();
Forth::CrossSection projector = Forth::CrossSection();

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastFPS = 0.0f;

void drawPrimitive(int mode, Forth::SimplexMode SM = Forth::SM_Tetrahedron)
{
	Forth::Buffer4 *buff = &tesseract.input;
	buff->Clear();
	buff->simplex = SM;
	switch (mode)
	{
	case 0:
		Forth::MeshGen::MakeHyperplane(*buff);
		break;
	case 1:
		Forth::MeshGen::MakePentatope(*buff);
		break;
	case 2:
		Forth::MeshGen::MakeTesseract(*buff);
		break;
	case 3:
		Forth::MeshGen::MakeHexdecahedroid(*buff);
		break;
	case 4:
		Forth::MeshGen::MakeIcosatetrahedroid(*buff);
		break;
	case 5:
		Forth::MeshGen::MakeHecatonicosahedroid(*buff);
		break;
	case 6:
		Forth::MeshGen::MakeHexacosidedroid(*buff);
		break;
	case 7:
		Forth::MeshGen::MakeHypersphere(*buff, 4);
		break;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, SCR_WIDTH = width, SCR_HEIGHT = height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	float Xpos = (float)xpos;
	float Ypos = (float)ypos;

	if (firstMouse)
	{
		lastX = Xpos;
		lastY = Ypos;
		firstMouse = false;
	}

	float xoffset = Xpos - lastX;
	float yoffset = lastY - Ypos; // reversed since y-coordinates go from bottom to top

	lastX = Xpos;
	lastY = Ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	for (int i = 0; i < 8; i++)
	{
		if (glfwGetKey(window, GLFW_KEY_1 + i) == GLFW_PRESS)
			drawPrimitive(i);
	}
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Forth Primitive Demo", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. Requires OpenGL 3.3\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfwSwapInterval(1);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	Shader sh("assets/vertex.vs", "assets/fragment.fs");

	GLuint vb;
	glGenBuffers(1, &vb);

	drawPrimitive(2);

	do
	{
		// per-frame time logic
		// --------------------
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (lastFPS + 0.5f < currentFrame) {
			std::cout << 1.f / max(0.0001f, deltaTime) << " FPS" << "\r";
			lastFPS = currentFrame;
		}
		// input
		// -----
		processInput(window);

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		sh.use();
		sh.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		sh.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		sh.setVec3("lightPos", glm::vec3(2.f, -2.f, 2.f));
		sh.setVec3("viewPos", camera.Position);

		// transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		sh.setMat4("projection", projection);
		sh.setMat4("view", view);
		sh.setMat4("model", model);

		// Render tesseract
		Forth::Transform4 r = Forth::Transform4::identity();
		float elapsed = float(glfwGetTime());
		r.rotation = Forth::Euler(1, elapsed * 75.f) *
					 Forth::Euler(4, elapsed * 90.f) *
					 Forth::Euler(5, elapsed * 105.f);

		tesseract.matrix = r;
		tesseract.Render(projector);

		FORTH_GL_DRAW(tesseract, vb);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
