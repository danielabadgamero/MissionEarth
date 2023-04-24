#ifndef VESSEL_H
#define VESSEL_H

#include <unordered_map>
#include <string>

#include <SDL.h>

struct Vec2
{
	double x{};
	double y{};
};

class Vessel
{
private:
	double mass{ 1000 };
	double dir{};
	double angle{};
	double dist{};
	Vec2 vel{};
	double fuel{};
	double thrust{};
	SDL_Texture* texture{};
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	Vessel();
	void draw() const;
	void move(double);
};

#endif