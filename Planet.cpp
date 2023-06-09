#include <string>
#include <cmath>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Planet.h"

Planet::Planet(std::string name, std::string parent, double m, double r, double a, double e, bool atmosphere, double surfaceDensity, double scaleHeight, SDL_Color atmosphereColor)
	: id{ name }, m{ m }, r{ r }, a{ a }, e{ e }, atmosphere{ atmosphere }, surfaceDensity{ surfaceDensity }, scaleHeight{ scaleHeight }, atmosphereColor{ atmosphereColor }
{
	SDL_Surface* tempSurface{ IMG_Load(("img/planets/" + name + ".png").c_str()) };
	icon = SDL_CreateTextureFromSurface(Core::renderer, tempSurface);
	id[0] -= 0x20;

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
		p = *std::find_if(Core::gameScreen->getPlanets().begin(), Core::gameScreen->getPlanets().end(), [&parent](Planet* A)
			{
				return A->getID() == parent;
			});

		double T{ 2 * M_PI * sqrt(pow(a, 3) / (G * p->m)) };
		n = 2 * M_PI / T;
	}

	SDL_FreeSurface(tempSurface);
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

	pos.x = a * (cos(E) - e) + p->pos.x;
	pos.y = a * sin(E) * sqrt(1 - pow(e, 2)) + p->pos.y;
}

SDL_Texture* Planet::getIcon() const
{
	return icon;
}

SDL_Rect Planet::draw() const
{
	Rect& viewport{ Core::gameScreen->getMap().getViewport() };
	SDL_Rect rect
	{
		static_cast<int>((pos.x - viewport.x + viewport.w / 2) / viewport.w * Core::monitor.w),
		static_cast<int>((pos.y - viewport.y + viewport.h / 2) / viewport.h * Core::monitor.h),
		std::clamp(static_cast<int>(r / viewport.w * Core::monitor.w), 10, INT_MAX),
		std::clamp(static_cast<int>(r / viewport.h * Core::monitor.h), 10, INT_MAX),
	};
	if (id == "Saturn")
		rect.w *= 2, rect.h *= 2;
	rect.x -= rect.w / 2;
	rect.y -= rect.h / 2;

	SDL_RenderCopy(Core::renderer, icon, NULL, &rect);

	if (id == "Saturn")
	{
		rect.w /= 2;
		rect.h /= 2;
		rect.x += rect.w / 2;
		rect.y += rect.h / 2;
	}
	return rect;
}

Planet* Planet::getSOI() const
{
	return p;
}

Point& Planet::getPos()
{
	return pos;
}

std::string& Planet::getID()
{
	return id;
}

double Planet::getM() const
{
	return m;
}

SDL_Color& Planet::getGroundColor()
{
	return groundColor;
}

double Planet::getEscapeVel(double radius) const
{
	double top{ 2 * G * m };
	double escapeVel{ sqrt(top / radius) };
	return escapeVel;
}