#include <algorithm>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "ControlRoom.h"
#include "Core.h"
#include "Planet.h"
#include "Widgets.h"
#include "Screens.h"

ControlRoom::ControlRoom()
{
	SOI = *std::find(Core::getPlanets().begin(), Core::getPlanets().end(), "earth");

	buttons["map"] = IMG_LoadTexture(Core::renderer, "img/mapButton.png");
}

void ControlRoom::draw() const
{
	Widgets::image(SOI->getIcon(), { Core::monitor.w / 3, Core::monitor.h / 2 }, { 0.5, 0.5 });

	if (Widgets::button(buttons.at("map"), { Core::monitor.w / 2, Core::monitor.h / 3 }, { 0, 0.5 }))
		Core::getScreen<GameScreen>(Core::game)->getView() = GameScreen::View::map;
}