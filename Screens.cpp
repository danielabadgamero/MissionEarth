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
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::levels)];

	if (Widgets::button(buttons.at("settings"), { Core::monitor.w / 2, Core::monitor.h / 2 + 150 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::settings)];

	if (Widgets::button(buttons.at("quit"), { Core::monitor.w / 2, Core::monitor.h / 2 + 300 }, { 0.5, 0.5 }))
		Core::running = false;
}

LevelsScreen::LevelsScreen()
{
	buttons["back"] = IMG_LoadTexture(Core::renderer, "img/backButton.png");

	SDLNet_ResolveHost(&ip, "api.api-ninjas.com", 80);

	for (const auto& file : std::filesystem::directory_iterator("img/planets/"))
		Core::levels.push_back(new Level{ file.path().filename().replace_extension().string()});

	Widgets::setFont("C:\\Windows\\Fonts\\AGENCYR.TTF", 32);

	thread = SDL_CreateThread(loadPlanetInfo, "loadPlanetInfo", NULL);
	while (!threadDone)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e));
		SDL_RenderClear(Core::renderer);

		Widgets::label("Loading planet ", { 30, Core::monitor.h - 30 }, { 0xff, 0x20, 0x20 }, { 0, 1 });

		SDL_RenderPresent(Core::renderer);
	}
	SDL_WaitThread(thread, NULL);
}

void LevelsScreen::draw() const
{
	if (Widgets::button(buttons.at("back"), { Core::monitor.w / 2, Core::monitor.h - 300 }, { 0.5, 0.5 }))
		Core::activeScreen = Core::screens[static_cast<int>(Core::ScreenType::home)];
}

int loadPlanetInfo(void*)
{
	for (Level* level : Core::levels)
		level->loadInfo();

	threadDone = true;
	return 0;
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
}

void GameScreen::draw() const
{
}