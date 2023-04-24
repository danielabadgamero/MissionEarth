#include <algorithm>

#include <SDL.h>

#include "ControlRoom.h"
#include "Core.h"
#include "Planet.h"
#include "Widgets.h"
#include "Screens.h"

ControlRoom::ControlRoom()
{
	std::vector<Planet*>& planets{ static_cast<GameScreen*>(Core::screens[static_cast<int>(Core::ScreenType::game)])->getPlanets() };
	SOI = *std::find(planets.begin(), planets.end(), "earth");
}

void ControlRoom::draw() const
{
	Widgets::image(SOI->getIcon(), { Core::monitor.w / 3, Core::monitor.h / 2 }, { 0.5, 0.5 });
}