#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>

#include "Core.h"
#include "Widgets.h"
#include "Screens.h"

void Core::init(const char* title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	SDLNet_Init();

	SDL_GetCurrentDisplayMode(0, &monitor);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, monitor.w, monitor.h, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	screens[static_cast<int>(ScreenType::home)] = new HomeScreen{};
	screens[static_cast<int>(ScreenType::worlds)] = new WorldsScreen{};
	screens[static_cast<int>(ScreenType::settings)] = new SettingsScreen{};
	screens[static_cast<int>(ScreenType::game)] = new GameScreen{};

	activeScreen = screens[static_cast<int>(ScreenType::home)];
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
			}
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouse.x, &mouse.y);
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

	SDLNet_Quit();
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