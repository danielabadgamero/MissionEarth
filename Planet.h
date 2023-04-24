#ifndef PLANET_H
#define PLANET_H

#include <string>

#include <SDL.h>

class Planet
{
private:
	SDL_Texture* icon{};
	std::string id{};
	Planet* p{};
	const double r{};
	const double m{};
	const double a{};
	const double e{};
	double M{};
	double n{};
	SDL_Color groundColor{};
	const bool atmosphere{};
	const double atmosphereHeight{};
	const double atmospherePressure{};
	SDL_Color atmosphereColor{};
	SDL_FPoint pos{};
public:
	bool operator==(std::string);
	void move(double);
	void draw() const;
	SDL_FPoint& getPos();
	Planet(std::string, std::string, double, double, double, double, bool = false, double = 0, double = 0, SDL_Color = {});
	SDL_Texture* getIcon() const;
};

#endif