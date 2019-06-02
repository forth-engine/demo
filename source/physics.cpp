
#include "common/utility.h"
#include "common/shaders.h"
#include "common/time.h"
#include "common/orbitview.h"

using namespace glm;
using namespace Forth;
using namespace Forth::Physics;

GLFWwindow *window;

// Classes necessary for rendering
OrbitView camera = OrbitView();
std::vector<Model4*> spheres = std::vector<Model4*>();
Model4 plane = Model4();
CrossSection projector = CrossSection();
Scene &scene = Scene();

void AddSphere()
{
	Model4* sphere = new Model4();
	sphere->rigidbody = new Body();
	Sphere* sp = new Sphere();
	scene.CreateBody(sphere->rigidbody);
	sphere->rigidbody->AddShape(sp);
	sphere->matrix = Transform4(Vector4(1, 5.f), Matrix4::identity());
	sphere->rigidbody->SetFlags(true, false, true, true, true);
	sphere->rigidbody->SetTransform(sphere->matrix);
	MeshGen::MakeHypersphere(sphere->input, 4, 0.5f);
	spheres.push_back(sphere);
}

void SetupPlane()
{
	plane.rigidbody = new Body();
	scene.CreateBody(plane.rigidbody);
	Box* b = new Box();
	b->extent = Vector4(5, 0.1f, 5, 5);
	plane.rigidbody->AddShape(b);
	plane.rigidbody->SetFlags(false, false, true, true, true);
	plane.matrix.rotation = Euler(2, 10);
	plane.rigidbody->SetTransform(plane.matrix);
	MeshGen::MakeHyperplane(plane.input, 5);
}

const char* help = R"(
	Lorem ipsum
	Navigation:
		A-Z
)";

int main(void)
{
	window = GlobalInit("Demo 2: Physics Playground", help, NULL, NULL, NULL);

	if (window == NULL)
		return -1;

	Shader sh("assets/vertex.vs", "assets/fragment.fs");

	// Shader setup (because shader stays all the time, it's safe to move it out the loop)
	sh.use();
	sh.setVec3("objectColor", 1.0f, 0.7f, 0.3f);
	sh.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	sh.setVec3("lightPos", vec3(2.f, -2.f, -2.f));
	sh.setVec3("viewPos", camera.GetPosition3D());

	// transformations (because 3d projection stays all the time, it's safe to move it out the loop)
	camera.position = vec3(0,5, 15);
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
	projector.Setup(Transform4::identity());

	do
	{
		// input
		MeasureTime();
		PrintFPS();

		// Clear the screen.
		GL_CLRSRC();

		scene.Step(deltaTime);

		for(auto sphere : spheres)
		{
			sphere->matrix = sphere->rigidbody->GetTransform();
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