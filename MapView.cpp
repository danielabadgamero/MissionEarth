#include <vector>
#include <cmath>

#include <SDL.h>

#include "MapView.h"
#include "Planet.h"
#include "Core.h"

MapView::MapView()
{
	viewport.w = 150e9f;
	viewport.h = 150e9f / Core::monitor.w * Core::monitor.h;
}

void MapView::move(double dt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LEFT)
	{
		viewport.x -= static_cast<float>(Core::mouseRel.x) / Core::monitor.w * viewport.w, Core::mouseRel.x = 0;
		viewport.y -= static_cast<float>(Core::mouseRel.y) / Core::monitor.h * viewport.h, Core::mouseRel.y = 0;
	}

	zoomFactor = pow(zoomFactor, 0.8);
	if (abs(zoomFactor - 1) < 1e-3)
		zoomFactor = 1;

	if (Core::wheel > 0)
		zoomFactor /= 1.1, Core::wheel = 0;
	else if (Core::wheel < 0)
		zoomFactor *= 1.1, Core::wheel = 0;

	if (zoomFactor > 1)
	{
		viewport.x += static_cast<float>((Core::savedPos.x - Core::monitor.w / 2.0f) / Core::monitor.w * viewport.w * (1 - zoomFactor));
		viewport.y += static_cast<float>((Core::savedPos.y - Core::monitor.h / 2.0f) / Core::monitor.h * viewport.h * (1 - zoomFactor));
		viewport.w *= static_cast<float>(zoomFactor);
		viewport.h *= static_cast<float>(zoomFactor);
	}
	else if (zoomFactor < 1)
	{
		viewport.w *= static_cast<float>(zoomFactor);
		viewport.h *= static_cast<float>(zoomFactor);
		viewport.x += static_cast<float>((Core::savedPos.x - Core::monitor.w / 2.0f) / Core::monitor.w * viewport.w * (1 - zoomFactor));
		viewport.y += static_cast<float>((Core::savedPos.y - Core::monitor.h / 2.0f) / Core::monitor.h * viewport.h * (1 - zoomFactor));
	}

	if (focusedPlanet)
	{
		viewport.x = Core::planets[focusedPlanet]->getPos().x;
		viewport.y = Core::planets[focusedPlanet]->getPos().y;
	}

	for (Planet*& planet : Core::planets)
		planet->move(dt);
}

void MapView::draw() const
{
	for (Planet*& planet : Core::planets)
		planet->draw();
}

SDL_FRect& MapView::getViewport()
{
	return viewport;
}