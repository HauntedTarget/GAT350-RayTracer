#include <iostream>
#include "Canvas.h"
#include "Renderer.h"
#include "Random.h"
#include "Ray.h"

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
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ Random::random01() * canvas.GetSize().x, Random::random01() * canvas.GetSize().y}, {Random::random01(), Random::random01(), Random::random01(), 1});
		canvas.Update();

		m_renderer.PresentCanvas(canvas);
	}

	m_renderer.Shutdown();

	return 0;
}