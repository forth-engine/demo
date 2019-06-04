
// Standard Includes
#include "common/orbitview.h"
#include "common/shaders.h"
#include "common/time.h"
#include "common/utility.h"

using namespace glm;
using namespace Forth;

#include <fstream>

GLFWwindow *window;

// Classes necessary for rendering
Model4 tesseract = Model4();
CrossSection projector = CrossSection();

// camera
OrbitView camera = OrbitView();
float lockedTime = -1.0f;

void drawPrimitive(int mode, SimplexMode SM = SM_Tetrahedron)
{
	Buffer4 *buff = &tesseract.input;
	buff->Clear();
	buff->simplex = SM;
	switch (mode)
	{
	case 0:
		MeshGen::MakeHyperplane(*buff);
		break;
	case 1:
		MeshGen::MakePentatope(*buff);
		break;
	case 2:
		MeshGen::MakeTesseract(*buff);
		break;
	case 3:
		MeshGen::MakeHexdecahedroid(*buff);
		break;
	case 4:
		MeshGen::MakeIcosatetrahedroid(*buff);
		break;
	case 5:
		MeshGen::MakeHecatonicosahedroid(*buff);
		break;
	case 6:
		MeshGen::MakeHexacosidedroid(*buff);
		break;
	case 7:
		MeshGen::MakeHypersphere(*buff, 4);
		break;
	case 8:
		MeshGen::MakeHypersphere(*buff, 4, 0.5f, Vector4(0.5f));
		break;
	case 9:
		for (int d = 0; d < 4; d++)
		{
			MeshGen::MakeTesseract(*buff);
			Vector4 s(0.5f - d * 0.1f);
			s[d] = 1.f + 0.2f * d;
			Transform4 t = Transform4::Scale(s) * Transform4::Position(Vector4(d, 0.5f + 0.1f * d));
			MeshGen::Transform(*buff, t);
		}

		break;
	}
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	camera.ProcessGLFWMouse(window, (float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		lockedTime = lockedTime == 0.f ? -1.f : 0.f;
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	for (int i = 0; i <= 9; i++)
	{
		if (glfwGetKey(window, GLFW_KEY_0 + i) == GLFW_PRESS)
			drawPrimitive(i);
	}
}

const char *help = R"(
	Shows primitive objects which mathematically defined by some articles and papers.
	Navigation:
		X, Y    Longitude-Latitude orbit view
		LMB + X Azimuth orbit view
		RMB     Resets orbit view to center
		Scroll  Zoom in/out
		Space   Stops or resumes model rotation
		0-9     Switch primitive object
)";

void SetupMaterial(Shader &sh)
{
	camera.position = vec3(0,0,-5.0f);

	// Shader setup (because shader stays all the time, it's safe to move it out the loop)
	sh.use();
	sh.setVec3("objectColor", 1.0f, 0.7f, 0.3f);
	sh.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	sh.setVec3("lightPos", vec3(2.f, 2.f, -2.f));
	sh.setVec3("viewPos", camera.GetPosition3D());

	// transformations (because 3d projection stays all the time, it's safe to move it out the loop)
	mat4 projection = camera.Get3DProjectionMatrix();
	mat4 view = camera.Get3DViewMatrix();
	mat4 model = mat4(1.0f);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setMat4("model", model);
}

int main(void)
{
	window = GlobalInit("Demo 1: 4D Object Primitives", help, mouse_callback, scroll_callback, key_callback);
	if (window == NULL)
		return -1;

	// Create and compile our GLSL program from the shaders
	Shader sh("assets/vertex.vs", "assets/fragment.fs");

	SetupMaterial(sh);

	CREATE_AND_BIND_VA(va);
	CREATE_VB(vb);

	drawPrimitive(2);

	do
	{
		// input
		MeasureTime();
		PrintFPS();
		processInput(window);

		// Clear the screen.
		GL_CLRSRC();

		// Render tesseract
		float elapsed = lockedTime >= 0.f ? lockedTime : float(glfwGetTime());
		auto r = Euler(1, elapsed * 75.f) *
				 Euler(4, elapsed * 90.f) *
				 Euler(5, elapsed * 105.f);

		projector.SetViewMatrix(camera.Get4DViewMatrix());
		tesseract.SetModelMatrix(Transform4::Rotation(r));
		tesseract.Render(projector);

		FORTH_GL_DRAW(tesseract, vb);

		// Swap buffers
		GL_SWAP(window);

	} while (glfwWindowShouldClose(window) == 0);

	glfwTerminate();

	return 0;
}
