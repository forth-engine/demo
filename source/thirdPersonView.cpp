
#include "common/orbitview.h"
#include "common/shaders.h"
#include "common/time.h"
#include "common/utility.h"

using namespace glm;
using namespace Forth;

GLFWwindow *window;
GLuint va;
GLuint vb;
Shader sh;
Model4 plane;
Model4 player;
CrossSection projector;
OrbitView camera;

float currentW = 0;
float targetW = 0;

void SetupPlayer()
{
	player.SetModelMatrix(Transform4::Position(Vector4(1, 1.f)));
	MeshGen::MakeHypersphere(player.input, 4, .5f, Vector4(1, .5f));
}

float randf(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

void SetupPlane()
{
	MeshGen::MakeHyperplane(plane.input, 5);
	plane.input.Align();
	for(int i = 0; i < 10; i++)
	{
		MeshGen::MakePentatope(plane.input, 1.f);
		auto t = Transform4(Vector4(randf(-5.f, 5.f),.5f,randf(-5.f, 5.f),randf(-5.f, 5.f)),
				Matrix4::identity);
		MeshGen::Transform(plane.input, t);
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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		targetW = Repeat(targetW + 90, 360);
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		targetW = Repeat(targetW + 90, 360);
	}
}

float speed = 2.f;

Matrix4 turntable(float w)
{
	return Euler(5, w);
}

void MovePlayer(Vector4 pos)
{
	player.SetModelMatrix(Transform4::Position(player.GetModelMatrix().position + turntable(-targetW) * pos));
}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MovePlayer(Vector4(0, -speed * deltaTime));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MovePlayer(Vector4(0, speed * deltaTime));
	// Right handed system: -Z is ahead of you
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MovePlayer(Vector4(2, -speed * deltaTime));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MovePlayer(Vector4(2, speed * deltaTime));
}

const char *help = R"(
	Lorem ipsum
	Navigation:
		A-Z
)";

void main_loop()
{
	MeasureTime();
	// PrintFPS();
	processInput(window);
	currentW = SmoothDamp(currentW, currentW + DeltaAngle(currentW, targetW), 3.f * deltaTime);

	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto p = player.GetModelMatrix().position;
	auto q = p;
	q = turntable(currentW) * q;
	q[3] = 0;
	auto r =
		camera.Get4DViewMatrix() *
		Transform4(q, Matrix4::identity) *
		Transform4(Vector4(), turntable(currentW)) *
		Transform4(-p, Matrix4::identity);

	projector.SetViewMatrix(r);

	plane.Render(projector);
	FORTH_GL_DRAW(plane, vb);

	player.Render(projector);
	FORTH_GL_DRAW(player, vb);

	// Swap buffers
	glfwSwapBuffers(window); glfwPollEvents();
}

int main(void)
{
	window = GlobalInit("Demo 4: Third Person View", help, mouse_callback, scroll_callback, key_callback);

	if (window == NULL)
		return -1;

	SetupPlane();
	SetupPlayer();

	projector.SetViewMatrix(Transform4(Vector4::zero, Euler(1, 45.f)));

	// Create and compile our GLSL program from the shaders
#if __EMSCRIPTEN__
	sh = Shader("assets/vertexES.vs", "assets/fragmentES.fs");
#else
	sh = Shader("assets/vertex.vs", "assets/fragment.fs");
#endif

	// Shader setup (because shader stays all the time, it's safe to move it out the loop)
	camera.position = vec3(0, 1.f, 15.f);
	sh.use();
	sh.setVec3("objectColor", 1.0f, 0.7f, 0.3f);
	sh.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	sh.setVec3("lightPos", vec3(5.f, 5.f, 5.f));
	sh.setVec3("viewPos", camera.GetPosition3D());

	// transformations (because 3d projection stays all the time, it's safe to move it out the loop)
	mat4 projection = camera.Get3DProjectionMatrix();
	mat4 view = camera.Get3DViewMatrix();
	mat4 model = mat4(1.0f);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setMat4("model", model);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glGenBuffers(1, &vb);

#if __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 0, 0);
#else
	do
	{
		main_loop();
	} while (glfwWindowShouldClose(window) == 0);
	glfwTerminate();
	return 0;
#endif
}