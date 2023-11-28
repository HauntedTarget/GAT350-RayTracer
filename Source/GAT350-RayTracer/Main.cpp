#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Ray.h"

using namespace std;
using namespace nc;

int main(int argc, char* argv[])
{
	cout << "Hello World!\n";

	Random::seedRandom(unsigned int(time(nullptr)));

	Renderer m_renderer;
	m_renderer.Initialize();
	m_renderer.CreateWindow("Hello World", 400, 300);

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
		}
	}

	m_renderer.Shutdown();

	return 0;
}