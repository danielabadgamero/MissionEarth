#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>

#include "ControlRoom.h"
#include "Map.h"
#include "Planet.h"
#include "Vessel.h"

class Screen
{
protected:
	std::unordered_map<std::string, SDL_Texture*> buttons{};
public:
	virtual void draw() const = 0;
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

class SettingsScreen : public Screen
{
private:
public:
	SettingsScreen();
	void draw() const override;
};

class GameScreen : public Screen
{
public:
	enum class View
	{
		controlRoom,
		map,
		vessel
	};
private:
	double* previousTime{};
	double* currentTime{};
	View currentView{};
	ControlRoom* controlRoom{};
	Map* map{};
	Vessel* vessel{};
	Planet* SOI{};
public:
	GameScreen();
	void draw() const override;
	View& getView();
	Map* getMap();
	Planet*& getSOI();
};

#endif