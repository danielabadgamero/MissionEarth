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

	Core::planets[1]->move(0.002);
	pos = { Core::planets[1]->getPos().x, static_cast<float>(Core::planets[1]->getPos().y + Core::planets[1]->getR()) + 100 };
	vel.y = Core::planets[1]->getVel().y;
}

void Vessel::move(double dt)
{
	for (Planet*& planet : Core::planets)
		planet->move(dt);

	double prevForce{};
	for (Planet*& planet : Core::planets)
		if (G * planet->getM() / pow(distance(planet->getPos(), pos), 2) > prevForce)
			Core::getScreen<GameScreen*>(Core::game)->getSOI() = planet;
	Planet* SOI{ Core::getScreen<GameScreen*>(Core::game)->getSOI() };

	if (SOI->getPos().x - pos.x != 0)
		vel.x += static_cast<float>(G * SOI->getM() / pow(SOI->getPos().x - pos.x, 2) * dt);
	if (SOI->getPos().y - pos.y != 0)
		vel.y += static_cast<float>(G * SOI->getM() / pow(SOI->getPos().y - pos.y, 2) * dt);

	if (SDL_GetKeyboardState(NULL)[SDLK_w])
		thrust += 1;
	if (SDL_GetKeyboardState(NULL)[SDLK_a])
		dir -= 1 * dt;
	if (SDL_GetKeyboardState(NULL)[SDLK_d])
		dir += 1 * dt;
	thrust = pow(thrust, 0.8);
	
	if (pos.y + vel.y * dt < SOI->getR() + SOI->getPos().y)
		vel.y *= -1;

	vel.x += sin(dir) * thrust / mass;
	vel.y += cos(dir) * thrust / mass;

	pos.x += static_cast<float>(vel.x * dt);
	pos.y += static_cast<float>(vel.y * dt);
}

void Vessel::draw() const
{
	Planet* SOI{ Core::getScreen<GameScreen*>(Core::game)->getSOI() };
	SDL_Rect ground{ 0, static_cast<int>(pos.y - SOI->getR()) + Core::monitor.h / 2, Core::monitor.w, Core::monitor.h };
	SDL_SetRenderDrawColor(Core::renderer, SOI->getGroundColor().r, SOI->getGroundColor().g, SOI->getGroundColor().b, 0xff);
	SDL_RenderFillRect(Core::renderer, &ground);

	SDL_Rect rect{ Core::monitor.w / 2, Core::monitor.h / 2 };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x -= rect.w / 2;
	rect.y -= rect.h / 2;

	SDL_RenderCopyEx(Core::renderer, texture, NULL, &rect, dir, NULL, SDL_FLIP_NONE);

	if (Widgets::button(buttons.at("back"), { 50, Core::monitor.h - 50 }, { 0, 1 }))
		Core::getScreen<GameScreen*>(Core::game)->getView() = GameScreen::View::controlRoom;
}