#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Screens.h"
#include "Widgets.h"

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
		Core::activeScreen = Core::screens[Core::levels];

	if (Widgets::button(buttons.at("settings"), { Core::monitor.w / 2, Core::monitor.h / 2 + 150 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[Core::settings];

	if (Widgets::button(buttons.at("quit"), { Core::monitor.w / 2, Core::monitor.h / 2 + 300 }, { 0.5, 0.5 }))
		Core::running = false;
}

LevelsScreen::LevelsScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void LevelsScreen::draw() const
{
	Widgets::setFont("C:\\Windows\\Fonts\\AGENCYR.TTF", 32);
	Widgets::label("Hello, world! Levels screen.", { Core::monitor.w / 2, Core::monitor.h / 2 }, { 0xff, 0xff, 0xff }, { 0.5, 0.5 });

	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[Core::home];
}

SettingsScreen::SettingsScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");
}

void SettingsScreen::draw() const
{
	Widgets::setFont("C:\\Windows\\Fonts\\AGENCYR.TTF", 32);
	Widgets::label("Hello, world! Settings screen. " + std::to_string(SDL_GetTicks() / 1000), {Core::monitor.w / 2, Core::monitor.h / 2}, {0xff, 0xff, 0xff}, {0.5, 0.5});

	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[Core::home];
}

GameScreen::GameScreen()
{
}

void GameScreen::draw() const
{
}