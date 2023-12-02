#include <iostream>
#include "Canvas.h"
#include "Renderer.h"
#include "Random.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

using namespace std;
using namespace nc;

int main(int argc, char* argv[])
{
	cout << "Hello World!\n";

	Random::seedRandom(unsigned int(time(nullptr)));
	cout << Random::random(5, 6);

	Renderer m_renderer;
	m_renderer.Initialize();
	m_renderer.CreateWindow("Hello World", 400, 300);

	Canvas canvas(400, 300, m_renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto material = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });

	// create objects -> add to scene
	auto sphere = std::make_unique<Sphere>(glm::vec3{ 12, 10, 2 }, 5, material);
	scene.AddObject(sphere);

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
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();

		m_renderer.PresentCanvas(canvas);
	}

	m_renderer.Shutdown();

	return 0;
}