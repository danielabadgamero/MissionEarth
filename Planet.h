#ifndef PLANET_H
#define PLANET_H

#include <string>

#include <SDL.h>

class Planet
{
private:
	SDL_Texture* icon{};
	std::string id{};
	double radius{};
	double mass{};
	SDL_Color groundColor{};
	bool atmosphere{};
	double atmosphereHeight{};
	double atmospherePressure{};
	SDL_Color atmosphereColor{};
public:
	Planet(std::string, double, double, bool = false, double = 0, double = 0, SDL_Color = {});
	void drawIcon(int);
};

#endif