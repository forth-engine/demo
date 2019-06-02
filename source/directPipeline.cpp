
#include "common/utility.h"

using namespace glm;
using namespace Forth;

GLFWwindow *window;

const char* help = R"(
	Lorem ipsum
	Navigation:
		A-Z
)";

int main(void)
{
	window = GlobalInit("Demo 4: Direct Pipeline (GPU/Hardware) Projection", help, NULL, NULL, NULL);

	if (window == NULL)
		return -1;

	do
	{
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwWindowShouldClose(window) == 0);

	glfwTerminate();

	return 0;
}