#ifndef VESSEL_H
#define VESSEL_H

#include <unordered_map>
#include <string>

#include <SDL.h>

class Vessel
{
private:
	double mass{ 1000 };
	double dir{};
	double fuel{};
	double thrust{};
	SDL_FPoint pos{};
	SDL_FPoint vel{};
	SDL_Texture* texture{};
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	Vessel();
	void draw() const;
	void move(double);
};

#endif