#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>

#include "Map.h"
#include "Planet.h"
#include "Vessel.h"
#include "ViewMode.h"

class Screen
{
protected:
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	virtual void draw() const = 0;
};

class SettingsScreen : public Screen
{
private:
public:
	SettingsScreen();
	void draw() const override;
};

class HomeScreen : public Screen
{
private:
	SDL_Texture* title{};
public:
	HomeScreen();
	void draw() const override;
};

class WorldsScreen : public Screen
{
private:
public:
	WorldsScreen();
	void draw() const override;
};

class GameScreen : public Screen
{
private:
	class Vessel
	{
	private:
		double mass{};
		double dir{};
		double angle{};
		double dist{};
		Vec2 vel{};
		double fuel{};
		double thrust{};
		SDL_Texture* texture{};
	public:
		Vessel();
		void draw() const;
		void move(double);
	};

	class Map
	{
	private:
		SDL_FRect viewport{};
		int focusedPlanet{};
		double zoomFactor{ 1 };
		std::unordered_map<std::string, SDL_Texture*> buttons{};
	public:
		int& getFocused();
		Map();
		void move(double);
		void draw() const;
		SDL_FRect& getViewport();
	};

	SDL_Texture* topPanelTexture{};
	std::vector<Planet*> planets{};
	Planet* SOI{};
public:
	GameScreen();
	void draw() const override;
};

#endif