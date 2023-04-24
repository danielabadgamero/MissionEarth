#ifndef PLANET_H
#define PLANET_H

#include <string>

#include <SDL.h>

class Planet
{
private:
	SDL_Texture* icon{};
	std::string id{};
	Planet* parent{};
	double r{};
	double m{};
	double a{};
	double e{};
	double n{};
	SDL_Color groundColor{};
	bool atmosphere{};
	double atmosphereHeight{};
	double atmospherePressure{};
	SDL_Color atmosphereColor{};
public:
	Planet(std::string, std::string, double, double, double, double, bool = false, double = 0, double = 0, SDL_Color = {});
};

#endif