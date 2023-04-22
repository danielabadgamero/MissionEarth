#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include <SDL.h>

class Level
{
private:
	SDL_Texture* icon{};
	SDL_Color groundColor{};
	std::string id{};
public:
	Level(std::string);
	void loadInfo();
};

#endif