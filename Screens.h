#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>
#include <SDL_net.h>

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

class LevelsScreen : public Screen
{
private:
	SDL_Thread* thread{};
public:
	LevelsScreen();
	void draw() const override;
};
inline IPaddress ip{};
inline TCPsocket socket{};
inline int loadPlanetInfo(void*);
inline bool threadDone{};

class SettingsScreen : public Screen
{
private:
public:
	SettingsScreen();
	void draw() const override;
};

class GameScreen : public Screen
{
private:
public:
	GameScreen();
	void draw() const override;
};

#endif