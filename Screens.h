#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>

#include "Planet.h"

struct Point;
struct Rect;

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
		double timer{};
		double aVel{};
		Point vel{};
		double fuel{};
		double thrust{};
		SDL_Texture* texture{};
	public:
		Vessel();
		void draw() const;
		void move(double);
		double& getDist();
		double getSpeed() const;
		void travel();
	};
	
	class Map
	{
	private:
		Rect viewport{};
		Planet* focusedPlanet{};
		std::vector<SDL_Rect> planetRects{};
		double zoomFactor{ 1 };
		std::string error{};
	public:
		Map();
		void move(double);
		void draw();
		Planet*& getFocused();
		Rect& getViewport();
		std::vector<SDL_Rect> getPlanetRects() const;
	};

	static inline enum class View
	{
		controlRoom,
		map,
		vessel,
	} currentView{};

	static inline double prevTime{};
	static inline double currTime{};
	static inline std::vector<Planet*> planets;
	static inline std::unordered_map<std::string, SDL_Texture*> buttons;
	static inline SDL_Texture* topPanelTexture;
	static inline Map map;
	static inline Vessel vessel;
	static inline Planet* SOI;
public:
	GameScreen();
	void draw() const override;
	Map& getMap();
	Vessel& getVessel();
	std::vector<Planet*>& getPlanets();
};

#endif