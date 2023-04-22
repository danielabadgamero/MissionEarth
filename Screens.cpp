#include <string>
#include <unordered_map>
#include <filesystem>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>

#include "Core.h"
#include "Screens.h"
#include "Widgets.h"
#include "Level.h"

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

	SDLNet_ResolveHost(&ip, "api.le-systeme-solaire.net", 80);

	for (const auto& file : std::filesystem::directory_iterator("img/planets/"))
		levels.push_back(new Level{ file.path().filename().string() });

	Widgets::setFont("C:\\Windows\\Fonts\\AGENCYR.TTF", 32);

	thread = SDL_CreateThread(loadPlanetInfo, "loadPlanetInfo", NULL);
	while (!threadDone)
	{
		SDL_FlushEvents(0, UINT32_MAX);
		SDL_RenderClear(Core::renderer);

		Widgets::label("Loading planet ", { 30, Core::monitor.h - 30 }, { 0xff, 0x20, 0x20 }, { 0.5, 1 });

		SDL_RenderPresent(Core::renderer);
	}
	SDL_WaitThread(thread, NULL);
}

void LevelsScreen::draw() const
{
	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[Core::home];
}

int loadPlanetInfo(void*)
{


	threadDone = true;
	return 0;
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