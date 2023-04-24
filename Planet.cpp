#include <string>
#include <cmath>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Planet.h"
#include "Screens.h"

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
		std::vector<Planet*>& planets{ static_cast<GameScreen*>(Core::screens[static_cast<int>(Core::ScreenType::game)])->getPlanets() };
		p = *std::find(planets.begin(), planets.end(), parent);

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

bool Planet::operator==(std::string B)
{
	return id == B;
}

SDL_Texture* Planet::getIcon() const
{
	return icon;
}