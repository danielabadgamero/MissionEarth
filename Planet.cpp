#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Planet.h"
#include "Screens.h"

Planet::Planet(std::string name, double radius, double mass, bool atmosphere, double atmosphereHeight, double atmospherePressure, SDL_Color atmosphereColor)
	: id{ name }, radius{ radius }, mass{ mass }, atmosphere{ atmosphere }, atmosphereHeight{ atmosphereHeight }, atmospherePressure{ atmospherePressure }, atmosphereColor{ atmosphereColor }
{
	SDL_Surface* tempSurface{ IMG_Load(("img/planets/" + name + ".png").c_str()) };
	icon = SDL_CreateTextureFromSurface(Core::renderer, tempSurface);
	int totalR{};
	int totalG{};
	int totalB{};
	for (int y{}; y != tempSurface->h; y++)
		for (int x{}; x != tempSurface->w; x++)
		{
			totalR += ((int*)tempSurface->pixels)[y * tempSurface->w + x] & tempSurface->format->Rmask;
			totalG += (((int*)tempSurface->pixels)[y * tempSurface->w + x] & tempSurface->format->Gmask) >> 8;
			totalB += (((int*)tempSurface->pixels)[y * tempSurface->w + x] & tempSurface->format->Bmask) >> 16;
		}
	totalR /= tempSurface->h * tempSurface->w;
	totalG /= tempSurface->h * tempSurface->w;
	totalB /= tempSurface->h * tempSurface->w;
	groundColor = { static_cast<Uint8>(totalR), static_cast<Uint8>(totalG), static_cast<Uint8>(totalB) };
}

void Planet::drawIcon(int pos)
{
	const int w{ Core::monitor.w / 2 };
	const int h{ Core::monitor.h / 2 };
	SDL_Rect rect{ Core::monitor.w / 4 + pos % (w * 256), 200 + pos / (h * 256), 128, 128 };
}