#include <string>
#include <cmath>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Planet.h"
#include "Screens.h"
#include "Map.h"

Planet::Planet(std::string name, std::string parent, double m, double r, double a, double e, bool atmosphere, double atmosphereHeight, double atmospherePressure, SDL_Color atmosphereColor)
	: id{ name }, m{ m }, r{ r }, a{ a }, e{ e }, atmosphere{ atmosphere }, atmosphereHeight{ atmosphereHeight }, atmospherePressure{ atmospherePressure }, atmosphereColor{ atmosphereColor }
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

	if (!parent.empty())
	{
		p = *std::find_if(Core::planets.begin(), Core::planets.end(), [&parent](Planet* A)
			{
				return A->getID() == parent;
			});

		double T{ 2 * M_PI * sqrt(pow(a, 3) / (G * p->m)) };
		n = 2 * M_PI / T;
	}
}

void Planet::move(double dt)
{
	if (!p)
		return;

	M += dt * n;
	double E{ M };
	while (true)
	{
		const double dE{ (E - e * sin(E) - M) / (1 - e * cos(E)) };
		E -= dE;
		if (abs(dE) < 1e-6) break;
	}

	pos.x = static_cast<float>(a * (cos(E) - e)) + p->pos.x;
	pos.y = static_cast<float>(a * sin(E) * sqrt(1 - pow(e, 2))) + p->pos.y;
}

SDL_Texture* Planet::getIcon() const
{
	return icon;
}

void Planet::draw() const
{
	SDL_FRect& viewport{ Core::getScreen<GameScreen*>(Core::game)->getMap()->getViewport() };
	SDL_FRect rect
	{
		(pos.x - viewport.x + viewport.w / 2.0f) / viewport.w * Core::monitor.w,
		(pos.y - viewport.y + viewport.h / 2.0f) / viewport.h * Core::monitor.h,
		std::clamp(static_cast<float>(r / viewport.w) * Core::monitor.w, 10.0f, FLT_MAX),
		std::clamp(static_cast<float>(r / viewport.h) * Core::monitor.h, 10.0f, FLT_MAX),
	};
	if (id == "saturn")
		rect.w *= 2.2f, rect.h *= 2.2f;
	rect.x -= rect.w / 2;
	rect.y -= rect.h / 2;

	SDL_RenderCopyF(Core::renderer, icon, NULL, &rect);
}

SDL_FPoint& Planet::getPos()
{
	return pos;
}

std::string& Planet::getID()
{
	return id;
}

double Planet::getR() const
{
	return r;
}

double Planet::getM() const
{
	return m;
}