#ifndef THUNDER_CORE
#define THUNDER_CORE

#include <vector>

#include <SDL.h>

#include "Screen.h"

namespace Core
{
	struct Thread
	{
		bool done{};
		int (*func)(void*){};
		SDL_Thread* thread{};

		void open();
		void close();
	};

	inline SDL_Window* window{};
	inline SDL_Renderer* renderer{};
	inline SDL_DisplayMode monitor{};
	inline SDL_Point mouse{};

	inline std::vector<Screen*> screens{};
	inline Screen* activeScreen{};
	inline bool running{};

	void init(const char*);
	void event();
	void draw();
	void quit();
}

#endif