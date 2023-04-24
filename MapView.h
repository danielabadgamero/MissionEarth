#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <SDL.h>

class MapView
{
private:
	SDL_FRect viewport{};
	int focusedPlanet{};
	double zoomFactor{ 1 };
public:
	MapView();
	void move(double);
	void draw() const;
	SDL_FRect& getViewport();
};

#endif