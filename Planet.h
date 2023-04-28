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
	const double m{};
	const double e{};
	double M{};
	double n{};
	SDL_Color groundColor{};
	Point pos{};
public:
	const bool atmosphere{};
	const double surfaceDensity{};
	const double scaleHeight{};
	const double a{};
	const double r{};
	SDL_Color atmosphereColor{};
	void move(double);
	double getEscapeVel(double) const;
	SDL_Rect draw() const;
	Point& getPos();
	std::string& getID();
	Planet(std::string, std::string, double, double, double, double, bool = false, double = 0, double = 0, SDL_Color = {});
	SDL_Texture* getIcon() const;
	double getM() const;
	Planet* getSOI() const;
	SDL_Color& getGroundColor();
};

#endif