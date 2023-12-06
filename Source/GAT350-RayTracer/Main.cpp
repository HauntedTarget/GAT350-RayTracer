#include <iostream>
#include <glm/gtx/color_space.hpp>
#include "Canvas.h"
#include "Renderer.h"
#include "Random.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"

using namespace std;
using namespace nc;

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);

int main(int argc, char* argv[])
{
	cout << "Hello World!\n";

	const int width = 1280;
	const int height = 640;
	const int samples = 20;
	const int depth = 5;

	Random::seedRandom(unsigned int(time(nullptr)));
	cout << Random::random(5, 6);

	Renderer m_renderer;
	m_renderer.Initialize();
	m_renderer.CreateWindow("Hello World", width, height);

	Canvas canvas(width, height, m_renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f }); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });
	auto lambertian2 = std::make_shared<Lambertian>(Color::color3_t{ 1, 0, 0 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 1, 1, 1 }, 0.0f);

	InitScene01(scene, canvas);

	//// create objects -> add to scene
	//for (int x = -1; x < 1; x++)
	//{
	//	for (int z = -5; z < 5; z++)
	//	{

	//		std::shared_ptr<Material> material;

	//		// create random material
	//		float r = Random::random01();
	//		if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
	//		else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
	//		else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
	//		else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

	//		// set random sphere radius
	//		float radius = Random::random(0.2f, 0.3f);
	//		// create sphere using random radius and material
	//		auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Random::random(-0.5f, 0.5f), radius, z + Random::random(-0.5f, 0.5f) }, radius, material);
	//		// add sphere to the scene
	//		scene.AddObject(std::move(sphere));
	//	}
	//}
	
	//for (int i = 0; i < 10; i++)
	//{
	//	std::shared_ptr<Material> material = ((int)Random::random(1,3) == 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
	//	auto sphere = std::make_unique<Sphere>(glm::vec3{ Random::random(-20, 20), Random::random(-20, 20), Random::random(-20, -50) }, 10, material);
	//	scene.AddObject(std::move(sphere));
	//}

	/*auto triangle = std::make_unique<Triangle>(glm::vec3{ 0,-1,0 }, glm::vec3{ 1,1,0 }, glm::vec3{0,1,0}, lambertian2);
	scene.AddObject(std::move(triangle));*/

	/*auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 0, 0 }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));*/

	//auto plane = std::make_unique<Plane>(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 1, 0 }, lambertian);
	//scene.AddObject(std::move(plane));

	// render scene 
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		m_renderer.PresentCanvas(canvas);
	}

	m_renderer.Shutdown();

	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = Random::random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = Random::random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Random::random(-0.5f, 0.5f), radius, z + Random::random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}