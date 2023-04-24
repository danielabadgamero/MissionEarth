#include <string>
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
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::worlds)];

	if (Widgets::button(buttons.at("settings"), { Core::monitor.w / 2, Core::monitor.h / 2 + 150 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::settings)];

	if (Widgets::button(buttons.at("quit"), { Core::monitor.w / 2, Core::monitor.h / 2 + 300 }, { 0.5, 0.5 }))
		Core::running = false;
}

WorldsScreen::WorldsScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void WorldsScreen::draw() const
{
	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::home)];
}

SettingsScreen::SettingsScreen()
{
	buttons["play"] = IMG_LoadTexture(Core::renderer, "img/playButton.png");
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void SettingsScreen::draw() const
{
	if (Widgets::button(buttons.at("play"), { Core::monitor.w / 2, Core::monitor.h + 300 }, { 0.5, 0 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::game)];

	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::home)];
}

GameScreen::GameScreen()
{
}

void GameScreen::draw() const
{
}