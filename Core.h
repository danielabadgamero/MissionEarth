#ifndef THUNDER_CORE
#define THUNDER_CORE

#include <vector>

#include <SDL.h>

#include "Screens.h"

constexpr double G{ 6.67428e-11 };

namespace Core
{
	struct Thread
	{
		bool done{};
		int (*func)(void*) {};
		SDL_Thread* thread{};

		void open();
		void close();
	};

	inline SDL_Window* window{};
	inline SDL_Renderer* renderer{};
	inline SDL_DisplayMode monitor{};
	inline SDL_Point mouse{};
	inline SDL_Point mouseRel{};
	inline SDL_FPoint savedPos{};
	inline SDL_Point clickPos{};
	
	inline HomeScreen* homeScreen{};
	inline SettingsScreen* settingsScreen{};
	inline WorldsScreen* worldsScreen{};
	inline GameScreen* gameScreen{};
	inline Screen* activeScreen{};

	inline bool running{};
	inline int wheel{};
	inline int timeWarp{ 1 };

	void init(const char*);
	void event();
	void draw();
	void quit();
}

#endif