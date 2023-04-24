#include <unordered_map>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Vessel.h"
#include "Core.h"
#include "Screens.h"
#include "Widgets.h"

Vessel::Vessel()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void Vessel::move(double dt)
{
	dt;
}

void Vessel::draw() const
{
	if (Widgets::button(buttons.at("back"), { 50, Core::monitor.h - 50 }, { 0, 1 }))
		Core::getScreen<GameScreen*>(Core::game)->getView() = GameScreen::View::controlRoom;
}