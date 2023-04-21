#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Widgets.h"
#include "Core.h"

void Label::draw(std::string text, SDL_Point pos, SDL_Color color, SDL_FPoint pivot)
{
	SDL_Surface* surface{ TTF_RenderText_Blended(font, text.c_str(), color) };
	SDL_Texture* texture{ SDL_CreateTextureFromSurface(Core::renderer, surface) };
	SDL_Rect rect{ pos.x, pos.y };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x -= static_cast<int>(rect.w * pivot.x);
	rect.y -= static_cast<int>(rect.h * pivot.y);
	SDL_RenderCopy(Core::renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Label::setFont(std::string path, int size)
{
	if (font)
		TTF_CloseFont(font);
	font = TTF_OpenFont(path.c_str(), size);
}

bool Button::draw(SDL_Texture* texture)
{

}