#ifndef THUNDER_CORE
#define THUNDER_CORE

#include <vector>

#include <SDL.h>

#include "Screens.h"

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

	enum
	{
		home,
		levels,
		settings,
		game,

		total_screens
	};

	inline SDL_Window* window{};
	inline SDL_Renderer* renderer{};
	inline SDL_DisplayMode monitor{};
	inline SDL_Point mouse{};

	inline std::vector<Screen*> screens{ total_screens };
	inline Screen* activeScreen{};
	inline bool running{};

	void init(const char*);
	void event();
	void draw();
	void quit();
}

#endif