#ifndef CONTROL_ROOM_H
#define CONTROL_ROOM_H

#include <unordered_map>

#include <SDL.h>

#include "Planet.h"

class ControlRoom
{
private:
	Planet* SOI{};
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	ControlRoom();
	void draw() const;
};

#endif