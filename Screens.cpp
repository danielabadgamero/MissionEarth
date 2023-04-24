#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Screens.h"
#include "Widgets.h"
#include "Planet.h"
#include "Map.h"
#include "Vessel.h"

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
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::worlds)];

	if (Widgets::button(buttons.at("settings"), { Core::monitor.w / 2, Core::monitor.h / 2 + 150 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::settings)];

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
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::game)];

	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::home)];
}

SettingsScreen::SettingsScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void SettingsScreen::draw() const
{
	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::home)];
}

GameScreen::GameScreen()
{
	Core::planets.push_back(new Planet{ "sun", "", 1.989e30, 696.34e6, 0, 0 });
	Core::planets.push_back(new Planet{ "earth", "sun", 5.9722e24, 6378.137e3, 149.598e9, 0.0167 });

	SOI = *std::find_if(Core::planets.begin(), Core::planets.end(), [](Planet* A) { return A->getID() == "earth"; });

	previousTime = new double{};
	currentTime = new double{};
	controlRoom = new ControlRoom{};
	map = new Map{};
	vessel = new Vessel{};
}

void GameScreen::draw() const
{
	*previousTime = *currentTime;
	*currentTime = SDL_GetTicks() / 1000.0;
	switch (currentView)
	{
	case View::controlRoom:
		controlRoom->draw();
		break;
	case View::map:
		map->move((*currentTime - *previousTime) * Core::timeWarp);
		map->draw();
		break;
	case View::vessel:
		vessel->move((*currentTime - *previousTime) * Core::timeWarp);
		vessel->draw();
		break;
	}
}

GameScreen::View& GameScreen::getView()
{
	return currentView;
}

Map* GameScreen::getMap()
{
	return map;
}

Planet*& GameScreen::getSOI()
{
	return SOI;
}