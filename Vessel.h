#ifndef VESSEL_H
#define VESSEL_H

#include <unordered_map>
#include <string>

#include <SDL.h>

class Vessel
{
private:
	SDL_FPoint pos{};
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	Vessel();
	void draw() const;
	void move(double);
};

#endif