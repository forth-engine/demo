
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
OrbitView camera = OrbitView();
std::vector<Model4 *> spheres = std::vector<Model4 *>();
Model4 plane = Model4();
CrossSection projector = CrossSection();
Scene &scene = Scene();

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
	for (int i = 0; i < 3; i++)
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
	plane.rigidbody->SetFlags(false, false, true, true, true);
	plane.rigidbody->SetTransform(plane.GetModelMatrix());
	MeshGen::MakeHyperplane(plane.input, 5);
}


void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		AddSphere();
	}
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

int main(void)
{
	window = GlobalInit("Demo 2: Physics Playground", help, mouse_callback, NULL, NULL);

	if (window == NULL)
		return -1;

	Shader sh("assets/vertex.vs", "assets/fragment.fs");

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

	AddSphere();
	SetupPlane();

	CREATE_AND_BIND_VA(va);
	CREATE_VB(vb);

	do
	{
		// input
		MeasureTime();
		PrintFPS();

		// Clear the screen.
		GL_CLRSRC();

		scene.Step(deltaTime);

		for (auto sphere : spheres)
		{
			if (sphere->rigidbody->IsAwake())
				sphere->SetModelMatrix(sphere->rigidbody->GetTransform());
			sphere->Render(projector);
			FORTH_GL_DRAW(*sphere, vb);
		}

		plane.Render(projector);
		FORTH_GL_DRAW(plane, vb);

		// Swap buffers
		GL_SWAP(window);

	} while (glfwWindowShouldClose(window) == 0);

	glfwTerminate();

	return 0;
}