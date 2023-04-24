#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <unordered_map>
#include <string>

#include <SDL.h>

class Map
{
private:
	SDL_FRect viewport{};
	int focusedPlanet{};
	double zoomFactor{ 1 };
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	int& getFocused();
	Map();
	void move(double);
	void draw() const;
	SDL_FRect& getViewport();
};

#endif