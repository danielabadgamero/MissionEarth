#ifndef LABEL_H
#define LABEL_H

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

namespace Widgets
{
	inline TTF_Font* font{};
	void setFont(std::string, int);

	void label(std::string, SDL_Point, SDL_Color, SDL_FPoint);
	bool button(SDL_Texture*, SDL_Point, SDL_FPoint);
	void image(SDL_Texture*, SDL_Point, SDL_FPoint);
}

#endif