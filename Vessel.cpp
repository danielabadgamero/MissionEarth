#include <unordered_map>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "Vessel.h"
#include "Core.h"
#include "Screens.h"
#include "Widgets.h"

static double distance(SDL_FPoint A, SDL_FPoint B)
{
	return static_cast<double>(sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)));
}

Vessel::Vessel()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
	texture = IMG_LoadTexture(Core::renderer, "img/spaceship.png");
}

void Vessel::move(double dt)
{
	double prevForce{};
	for (Planet*& planet : Core::planets)
		if (G * planet->getM() / pow(planet->getR(), 2) > prevForce)
			Core::getScreen<GameScreen*>(Core::game)->getSOI() = planet;
	Planet* SOI{ Core::getScreen<GameScreen*>(Core::game)->getSOI() };

	vel.x += G * SOI->getM() / pow(SOI->getR(), 2);
	vel.y += G * SOI->getM() / pow(SOI->getR(), 2);
}

void Vessel::draw() const
{
	if (Widgets::button(buttons.at("back"), { 50, Core::monitor.h - 50 }, { 0, 1 }))
		Core::getScreen<GameScreen*>(Core::game)->getView() = GameScreen::View::controlRoom;
}