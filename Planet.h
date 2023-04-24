#ifndef PLANET_H
#define PLANET_H

#include <string>

#include <SDL.h>

struct Point
{
	double x{};
	double y{};
};

struct Rect
{
	double x{};
	double y{};
	double w{};
	double h{};
};

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
	Point pos{};
public:
	void move(double);
	void draw() const;
	Point& getPos();
	std::string& getID();
	Planet(std::string, std::string, double, double, double, double, bool = false, double = 0, double = 0, SDL_Color = {});
	SDL_Texture* getIcon() const;
	double getR() const;
	double getM() const;
	SDL_Color& getGroundColor();
};

#endif