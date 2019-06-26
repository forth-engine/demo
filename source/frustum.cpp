
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
Frustum4 projector = Frustum4();

// camera
OrbitView camera = OrbitView();
float lockedTime = -1.0f;
SimplexMode SM = SM_Triangle;
int Shape = 2;

void drawPrimitive()
{
	Buffer4 *buff = &tesseract.input;
	buff->Clear();
	buff->simplex = SM;
	switch (Shape)
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
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_SPACE)
		{
			lockedTime = lockedTime == 0.f ? -1.f : 0.f;
		}
		if (key == GLFW_KEY_F3)
		{
			SM = SM_Triangle;
			drawPrimitive();
		}
		if (key == GLFW_KEY_F2)
		{
			SM = SM_Line;
			drawPrimitive();
		}
		if (key == GLFW_KEY_F1)
		{
			SM = SM_Point;
			drawPrimitive();
		}
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);

		for (int i = 0; i <= 9; i++)
		{
			if (key == GLFW_KEY_0 + i)
			{
				Shape = i;
				drawPrimitive();
			}
		}
	}
}


const char *help = R"(
	Shows primitive objects using frustum projection.
	Navigation:
		X, Y    Longitude-Latitude orbit view
		LMB + X Azimuth orbit view
		RMB     Resets orbit view to center
		Scroll  Zoom in/out
		Space   Stops or resumes model rotation
		0-9     Switch primitive object
		F1-F3   Switch Point/Wire/Solid visualization
)";

void SetupMaterial(Shader &sh)
{

	// Shader setup (because shader stays all the time, it's safe to move it out the loop)
	sh.use();
	sh.setVec3("objectColor", 1.0f, 0.7f, 0.3f);
	sh.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	sh.setVec3("lightPos", vec3(3.f, 2.f, -3.f));
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
	window = GlobalInit("Demo 3: Frustum", help, mouse_callback, scroll_callback, key_callback);
	if (window == NULL)
		return -1;

	// Create and compile our GLSL program from the shaders
#if __EMSCRIPTEN__
	Shader sh("assets/vertexES.vs", "assets/fragmentES.fs");
#else
	Shader sh("assets/vertex.vs", "assets/fragment.fs");
#endif

	SetupMaterial(sh);

	CREATE_AND_BIND_VA(va);
	CREATE_VB(vb);

	drawPrimitive();

	do
	{
		// input
		MeasureTime();
		PrintFPS();

		// Clear the screen.
		GL_CLRSRC();

		// Render tesseract
		float elapsed = lockedTime >= 0.f ? lockedTime : float(glfwGetTime());
		auto r = Euler(1, elapsed * 75.f) *
			Euler(4, elapsed * 90.f) *
			Euler(5, elapsed * 105.f);

		projector.SetViewMatrix(Transform4::Position(Vector4(3, 2.f)) * camera.Get4DViewMatrix());
		projector.focalLength = 0.25f;
		projector.Setup();
		tesseract.SetModelMatrix(Transform4::Rotation(r));
		tesseract.Render(projector);

		FORTH_GL_DRAW(tesseract, vb);

		// Swap buffers
		GL_SWAP(window);

	} while (glfwWindowShouldClose(window) == 0);

	glfwTerminate();

	return 0;
}
