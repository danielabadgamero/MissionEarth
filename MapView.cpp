#include <vector>

#include <SDL.h>

#include "MapView.h"
#include "Planet.h"
#include "Core.h"

MapView::MapView()
{

}

void MapView::move(double dt)
{
	for (Planet*& planet : Core::getPlanets())
		planet->move(dt);
}

void MapView::draw() const
{
	for (Planet*& planet : Core::getPlanets())
		planet->draw();
}

SDL_FRect& MapView::getViewport()
{
	return viewport;
}