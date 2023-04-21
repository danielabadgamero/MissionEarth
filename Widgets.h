#ifndef LABEL_H
#define LABEL_H

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

namespace Label
{
	inline TTF_Font* font{};

	void draw(std::string, SDL_Point, SDL_Color, SDL_FPoint);
	void setFont(std::string, int);
}

namespace Button
{
	bool draw(SDL_Texture*, SDL_Point, SDL_FPoint);
}

namespace Image
{

}

#endif