
#include "common/orbitview.h"
#include "common/shaders.h"
#include "common/time.h"
#include "common/utility.h"
#include <random>

using namespace glm;
using namespace Forth;
using namespace Forth::Physics;

GLFWwindow *window;

// Classes necessary for rendering
OrbitView camera;
std::vector<Model4 *> spheres;
GLuint va;
GLuint vb;
Shader sh;
Model4 plane;
CrossSection projector;
Scene scene;
Euler4 currentTilt;
Euler4 targetTilt;

void AddSphere()
{
	Model4 *sphere = new Model4();
	sphere->rigidbody = new Body();
	Sphere *sp = new Sphere();
	scene.CreateBody(sphere->rigidbody);
	sphere->rigidbody->AddShape(sp);
	sphere->SetModelMatrix(Transform4(Vector4(1, 5.f), Matrix4::identity));
	sphere->rigidbody->SetFlags(true, false, true, true, true);
	sphere->rigidbody->SetTransform(sphere->GetModelMatrix());
	sphere->rigidbody->SetLinearVelocity(Vector4(1, 4.f));
	sphere->input.simplex = SM_Tetrahedron;
	MeshGen::MakeHypersphere(sphere->input, 4, 0.5f);
	spheres.push_back(sphere);
}

void RemoveSphere()
{
	if (spheres.empty()) return;
	auto sphere = spheres[std::rand() % spheres.size()];
	scene.RemoveBody(sphere->rigidbody);
	delete sphere;
}

void SetupPlane()
{
	plane.rigidbody = new Body();
	scene.CreateBody(plane.rigidbody);
	plane.SetModelMatrix(Transform4::Rotation(Euler(2, 5)));
	// Box on 8 sides
	for (int i = 0; i < 4; i++)
	{
		for (float s = -1.f; s <= 1.f; s += 2)
		{
			Box *b = new Box();
			b->extent = Vector4(5);
			b->extent[i] = 0.1f;
			b->local.position = Vector4(1, 5.f) + Vector4(i, s * 5.f);
			plane.rigidbody->AddShape(b);
		}
	}
	plane.rigidbody->SetFlags(false, true, true, true, true);
	plane.rigidbody->SetTransform(plane.GetModelMatrix());
	plane.input.simplex = SM_Tetrahedron;
	MeshGen::MakeHyperplane(plane.input, 5);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	camera.ProcessGLFWMouse(window, (float)xpos, (float)ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	const float tiltCoeff = 10.f;
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			targetTilt.x += tiltCoeff;
		if (key == GLFW_KEY_S)
			targetTilt.x += -tiltCoeff;
		if (key == GLFW_KEY_A)
			targetTilt.z += tiltCoeff;
		if (key == GLFW_KEY_D)
			targetTilt.z += -tiltCoeff;
		if (key == GLFW_KEY_E)
			targetTilt.u += tiltCoeff;
		if (key == GLFW_KEY_Q)
			targetTilt.u += -tiltCoeff;
		if (key == GLFW_KEY_EQUAL)
			AddSphere();
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);

	}
	else if (action == GLFW_RELEASE)
	{
		// if (key == GLFW_KEY_W)
		// 	targetTilt.x = 0;
		// if (key == GLFW_KEY_S)
		// 	targetTilt.x = 0;
		// if (key == GLFW_KEY_A)
		// 	targetTilt.z = 0;
		// if (key == GLFW_KEY_D)
		// 	targetTilt.z = 0;
		// if (key == GLFW_KEY_E)
		// 	targetTilt.u = 0;
		// if (key == GLFW_KEY_Q)
		// 	targetTilt.u = 0;
	}
}


void SetupMaterial(Shader &sh)
{
// Shader setup (because shader stays all the time, it's safe to move it out the loop)
	sh.use();
	sh.setVec3("objectColor", 1.0f, 0.7f, 0.3f);
	sh.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	sh.setVec3("lightPos", vec3(4.f, 4.f, 4.f));
	sh.setVec3("viewPos", camera.GetPosition3D());

	// transformations (because 3d projection stays all the time, it's safe to move it out the loop)
	camera.position = vec3(0, 5, 15);
	mat4 projection = camera.Get3DProjectionMatrix();
	mat4 view = camera.Get3DViewMatrix();
	mat4 model = mat4(1.0f);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setMat4("model", model);
}

const char *help = R"(
	Demonstrating physics module in Forth Engine.
	Navigation:
		Space                 Add a sphere
		Backspace             Delete a random sphere
		Mouse X, Y            Longitude-Latitude orbit view
		Ctrl+X Mouse/Scroll   Azimuth orbit view
		WASD                  Tilt the plane
		LMB/RMB               Attractive / Pulse Force
)";

void main_loop()
{
		// input
		MeasureTime();
		PrintFPS();

		// Clear the screen.
		GL_RESET();

		projector.SetViewMatrix(camera.Get4DViewMatrix());
		// projector.focalLength = 0.4f;
		// projector.useFrustumCulling = false;
		// projector.Setup();
		scene.Step(deltaTime);

		for (auto sphere : spheres)
		{
			if (sphere->rigidbody->IsAwake())
				sphere->SetModelMatrix(sphere->rigidbody->GetTransform());
			sphere->Render(projector);
			FORTH_GL_DRAW(*sphere, vb);
		}

		for(size_t i = 0; i < 6; i++)
		{
			currentTilt[i] = SmoothDamp(currentTilt[i], targetTilt[i], deltaTime * 3.f);
		}

		plane.SetModelMatrix(Transform4::Rotation(Euler(4, currentTilt.u)*Euler(2, currentTilt.z)*Euler(0, currentTilt.x)));
		plane.Render(projector);
		FORTH_GL_DRAW(plane, vb);

		// Swap buffers
		GL_SWAP(window);
}

int main(void)
{
	window = GlobalInit("Demo 2: Physics Playground", help, mouse_callback, NULL, key_callback);

	if (window == NULL)
		return -1;

	sh = Shader(COMMON_SHADER);

	SetupMaterial(sh);

	AddSphere();
	SetupPlane();

	BIND_VA_VB(va, vb);

	MAIN_LOOP;
}