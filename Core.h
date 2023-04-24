#ifndef THUNDER_CORE
#define THUNDER_CORE

#include <vector>

#include <SDL.h>

#include "Screens.h"
#include "Planet.h"

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

	enum ScreenType
	{
		home,
		worlds,
		settings,
		game,

		total_screens
	};

	inline SDL_Window* window{};
	inline SDL_Renderer* renderer{};
	inline SDL_DisplayMode monitor{};
	inline SDL_Point mouse{};
	inline SDL_Point mouseRel{};
	inline SDL_FPoint savedPos{};
	inline SDL_Point clickPos{};

	inline std::vector<Screen*> screens{ total_screens };
	inline std::vector<Planet*> planets{};
	inline Screen* activeScreen{};
	inline bool running{};
	inline int wheel{};
	inline int timeWarp{ 1 };

	void init(const char*);
	void event();
	void draw();
	void quit();

	template <typename T>
	T getScreen(ScreenType screen)
	{
		return static_cast<T>(screens[screen]);
	}
}

#endif