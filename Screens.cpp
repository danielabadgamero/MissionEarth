#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Screens.h"
#include "Widgets.h"
#include "Planet.h"

HomeScreen::HomeScreen()
{
	title = IMG_LoadTexture(Core::renderer, "img/title.png");
	buttons["play"] = IMG_LoadTexture(Core::renderer, "img/playButton.png");
	buttons["settings"] = IMG_LoadTexture(Core::renderer, "img/settingsButton.png");
	buttons["quit"] = IMG_LoadTexture(Core::renderer, "img/quitButton.png");
}

void HomeScreen::draw() const
{
	Widgets::image(title, { Core::monitor.w / 2, 0 }, { 0.5, 0 });

	if (Widgets::button(buttons.at("play"), { Core::monitor.w / 2, Core::monitor.h / 2 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::worldsScreen;

	if (Widgets::button(buttons.at("settings"), { Core::monitor.w / 2, Core::monitor.h / 2 + 150 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::settingsScreen;

	if (Widgets::button(buttons.at("quit"), { Core::monitor.w / 2, Core::monitor.h / 2 + 300 }, { 0.5, 0.5 }))
		Core::running = false;
}

WorldsScreen::WorldsScreen()
{
	buttons["play"] = IMG_LoadTexture(Core::renderer, "img/playButton.png");
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void WorldsScreen::draw() const
{
	if (Widgets::button(buttons.at("play"), { Core::monitor.w / 2, 300 }, { 0.5, 0 }))
		Core::activeScreen = Core::gameScreen;

	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::homeScreen;
}

SettingsScreen::SettingsScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void SettingsScreen::draw() const
{
	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::homeScreen;
}

GameScreen::GameScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
	buttons["map"] = IMG_LoadTexture(Core::renderer, "img/mapButton.png");
	buttons["vessel"] = IMG_LoadTexture(Core::renderer, "img/vesselButton.png");

	topPanelTexture = IMG_LoadTexture(Core::renderer, "img/topPanelInfo.png");

	planets.push_back(new Planet{ "sun", "", 1.989e30, 696.34e6, 0, 0 });
	planets.push_back(new Planet{ "earth", "Sun", 5.9722e24, 6378.137e3, 149.598e9, 0.0167 });

	map = Map{};
	vessel = Vessel{};

	SOI = *std::find_if(planets.begin(), planets.end(), [](Planet* A) { return A->getID() == "Earth"; });
	vessel.getDist() = SOI->getR() + 100;
}

void GameScreen::draw() const
{
	prevTime = currTime;
	currTime = SDL_GetTicks() / 1000.0;

	map.move((currTime - prevTime) * Core::timeWarp);
	vessel.move((currTime - prevTime) * Core::timeWarp);

	switch (currentView)
	{
	case View::controlRoom:
		Widgets::image(SOI->getIcon(), { Core::monitor.w / 3, Core::monitor.h / 2 }, { 0.5, 0.5 });
		Widgets::image(topPanelTexture, { Core::monitor.w / 2, 0 }, { 0.5, 0 });

		Widgets::setFont("C:\\Windows\\Fonts\\AGENCYB.TTF", 50);
		Widgets::label(SOI->getID().c_str(), { Core::monitor.w / 2, 0 }, { 0x28, 0x00, 0xbe }, { 0.5, 0 });

		if (Widgets::button(buttons.at("map"), { Core::monitor.w / 2, Core::monitor.h / 3 }, { 0, 0.5 }))
			currentView = View::map;

		if (Widgets::button(buttons.at("vessel"), { Core::monitor.w / 2, Core::monitor.h / 3 + 200 }, { 0, 0.5 }))
			currentView = View::vessel;
		break;
	case View::map:
		map.draw();
		break;
	case View::vessel:
		vessel.draw();
		break;
	}
}

GameScreen::Vessel::Vessel()
{
	texture = IMG_LoadTexture(Core::renderer, "img/spaceship.png");
	mass = 1000;
}

void GameScreen::Vessel::move(double dt)
{
	timer += dt;
	vel.y -= G * SOI->getM() / pow(dist, 2) * dt;

	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
		thrust = 100000;
	else
		thrust = 0;
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])
		dir -= 100 * dt;
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])
		dir += 100 * dt;

	if (dist + vel.y * dt < SOI->getR())
		vel.y *= -0.1f, vel.x *= 0.8;
	else
	{
		vel.x += sin(dir * M_PI / 180) * thrust / mass * dt;
		vel.y += cos(dir * M_PI / 180) * thrust / mass * dt + (sqrt(pow(dist, 2) + pow(vel.x, 2)) - dist) * dt;
	}

	dist += vel.y * dt;
	angle += atan(vel.x * dt / dist) * 180 / M_PI;
}

void GameScreen::Vessel::draw() const
{
	SDL_Rect ground{ 0, static_cast<int>(dist - SOI->getR()) + Core::monitor.h / 2, Core::monitor.w, Core::monitor.h };
	SDL_SetRenderDrawColor(Core::renderer, SOI->getGroundColor().r, SOI->getGroundColor().g, SOI->getGroundColor().b, 0xff);
	SDL_RenderFillRect(Core::renderer, &ground);

	SDL_Rect rect{ Core::monitor.w / 2, Core::monitor.h / 2 };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x -= rect.w / 2;
	rect.y -= rect.h;

	SDL_RenderCopyEx(Core::renderer, texture, NULL, &rect, dir, NULL, SDL_FLIP_NONE);

	if (Widgets::button(buttons.at("back"), { 50, Core::monitor.h - 50 }, { 0, 1 }))
		currentView = View::controlRoom;

	Widgets::label("V-Speed: " + std::to_string(vel.y), { 10, 0 }, { 0xff, 0xff, 0xff }, {});
	Widgets::label("H-Speed: " + std::to_string(vel.x), { 10, 50 }, { 0xff, 0xff, 0xff }, {});
	Widgets::label("Height: " + std::to_string((dist - SOI->getR()) / 1000), { 10, 100 }, { 0xff, 0xff, 0xff }, {});
	Widgets::label("Angle: " + std::to_string(angle), { 10, 150 }, { 0xff, 0xff, 0xff }, {});
	Widgets::label("Time: " + std::to_string(timer), { 10, 200 }, { 0xff, 0xff, 0xff }, {});
}

double& GameScreen::Vessel::getDist()
{
	return dist;
}

GameScreen::Map::Map()
{
	viewport.w = 150e9f;
	viewport.h = 150e9f / Core::monitor.w * Core::monitor.h;
}

void GameScreen::Map::move(double dt)
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
		viewport.x += (Core::savedPos.x - Core::monitor.w / 2.0f) / Core::monitor.w * viewport.w * (1 - zoomFactor);
		viewport.y += (Core::savedPos.y - Core::monitor.h / 2.0f) / Core::monitor.h * viewport.h * (1 - zoomFactor);
		viewport.w *= zoomFactor;
		viewport.h *= zoomFactor;
	}
	else if (zoomFactor < 1)
	{
		viewport.x += (Core::savedPos.x - Core::monitor.w / 2.0f) / Core::monitor.w * viewport.w * (1 - zoomFactor);
		viewport.y += (Core::savedPos.y - Core::monitor.h / 2.0f) / Core::monitor.h * viewport.h * (1 - zoomFactor);
		viewport.w *= zoomFactor;
		viewport.h *= zoomFactor;
	}

	if (focusedPlanet)
	{
		viewport.x = Core::gameScreen->planets[focusedPlanet]->getPos().x;
		viewport.y = Core::gameScreen->planets[focusedPlanet]->getPos().y;
	}

	for (Planet*& planet : Core::gameScreen->planets)
		planet->move(dt);
}

void GameScreen::Map::draw() const
{
	for (Planet*& planet : Core::gameScreen->planets)
		planet->draw();

	if (Widgets::button(buttons.at("back"), { 50, Core::monitor.h - 50 }, { 0, 1 }))
		currentView = View::controlRoom;
}

Rect& GameScreen::Map::getViewport()
{
	return viewport;
}

int& GameScreen::Map::getFocused()
{
	return focusedPlanet;
}

GameScreen::Map& GameScreen::getMap()
{
	return map;
}

GameScreen::Vessel& GameScreen::getVessel()
{
	return vessel;
}

std::vector<Planet*>& GameScreen::getPlanets()
{
	return planets;
}