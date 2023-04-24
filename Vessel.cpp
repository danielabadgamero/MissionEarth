#include <unordered_map>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "Vessel.h"
#include "Core.h"
#include "Screens.h"
#include "Widgets.h"

Vessel::Vessel()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
	texture = IMG_LoadTexture(Core::renderer, "img/spaceship.png");

	dist = Core::planets[1]->getR();
	Core::getScreen<GameScreen*>(Core::game)->getSOI() == Core::planets[1];
}

void Vessel::move(double dt)
{
	for (Planet*& planet : Core::planets)
		planet->move(dt);
	Planet* SOI{ Core::getScreen<GameScreen*>(Core::game)->getSOI() };
	
	vel.y -= static_cast<float>(G * SOI->getM() / pow(dist, 2) * dt);

	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
		thrust = 20000;
	else
		thrust = 0;
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])
		dir -= 200 * dt;
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])
		dir += 200 * dt;
	
	if (dist + vel.y * dt < SOI->getR())
		vel.y *= -0.1f, vel.x *= 0.8;
	else
	{
		vel.x += sin((dir) * M_PI / 180) * thrust / mass;
		vel.y += cos((dir) * M_PI / 180) * thrust / mass;
	}

	dist += vel.y * dt;
	angle += atan(vel.x * dt / dist) * 180 / M_PI;

	Widgets::label("Speed: " + std::to_string(vel.y), { 10, 0 }, { 0xff, 0xff, 0xff }, {});
	Widgets::label("Height: " + std::to_string((dist - SOI->getR()) / 1000), { 10, 50 }, { 0xff, 0xff, 0xff }, {});
	Widgets::label("Angle: " + std::to_string(angle), { 10, 100 }, { 0xff, 0xff, 0xff }, {});
}

void Vessel::draw() const
{
	Planet* SOI{ Core::getScreen<GameScreen*>(Core::game)->getSOI() };
	SDL_Rect ground{ 0, static_cast<int>(dist - SOI->getR()) + Core::monitor.h / 2, Core::monitor.w, Core::monitor.h };
	SDL_SetRenderDrawColor(Core::renderer, SOI->getGroundColor().r, SOI->getGroundColor().g, SOI->getGroundColor().b, 0xff);
	SDL_RenderFillRect(Core::renderer, &ground);

	SDL_Rect rect{ Core::monitor.w / 2, Core::monitor.h / 2 };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x -= rect.w / 2;
	rect.y -= rect.h;

	SDL_RenderCopyEx(Core::renderer, texture, NULL, &rect, dir, NULL, SDL_FLIP_NONE);

	if (Widgets::button(buttons.at("back"), { 50, Core::monitor.h - 50 }, { 0, 1 }))
		Core::getScreen<GameScreen*>(Core::game)->getView() = GameScreen::View::controlRoom;
}