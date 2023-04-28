#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Core.h"
#include "Widgets.h"
#include "Screens.h"

void Core::init(const char* title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_GetCurrentDisplayMode(0, &monitor);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, monitor.w, monitor.h, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	homeScreen = new HomeScreen{};
	settingsScreen = new SettingsScreen{};
	worldsScreen = new WorldsScreen{};
	gameScreen = new GameScreen{};

	activeScreen = homeScreen;
	running = true;
}

void Core::event()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				running = false;
				break;
			case SDL_SCANCODE_COMMA:
				if (timeWarp > 1)
					timeWarp /= 10;
				break;
			case SDL_SCANCODE_PERIOD:
				timeWarp *= 10;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouse.x, &mouse.y);
			mouseRel.x = e.motion.xrel;
			mouseRel.y = e.motion.yrel;
			break;
		case SDL_MOUSEWHEEL:
			savedPos.x = static_cast<float>(mouse.x);
			savedPos.y = static_cast<float>(mouse.y);
			wheel = e.wheel.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			clickPos.x = mouse.x;
			clickPos.y = mouse.y;
			if (activeScreen == gameScreen)
			{
				gameScreen->getMap().getFocused() = 0;
				std::vector<SDL_Rect> planetRects{ gameScreen->getMap().getPlanetRects() };
				for (std::vector<SDL_Rect>::iterator rect{ planetRects.begin() }; rect != planetRects.end(); rect++)
					if (SDL_PointInRect(&clickPos, &(*rect)))
					{
						gameScreen->getMap().getFocused() = static_cast<int>(std::distance(planetRects.begin(), rect));
						break;
					}
			}
			break;
		}
	}
}

void Core::draw()
{
	SDL_SetRenderDrawColor(renderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderClear(renderer);

	activeScreen->draw();

	SDL_RenderPresent(renderer);
}

void Core::quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Core::Thread::open()
{
	thread = SDL_CreateThread(func, "thread", NULL);
}

void Core::Thread::close()
{
	SDL_WaitThread(thread, NULL);
}