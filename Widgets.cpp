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

bool Button::draw(SDL_Texture* texture, SDL_Point pos, SDL_FPoint pivot)
{
	SDL_Rect rect{ pos.x, pos.y};
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x -= static_cast<int>(rect.w * pivot.x);
	rect.y -= static_cast<int>(rect.h * pivot.y);
	if (SDL_PointInRect(&Core::mouse, &rect))
		SDL_SetTextureColorMod(texture, 0xf0, 0xf0, 0xf0);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LEFT)
	{
		SDL_SetTextureColorMod(texture, 0x40, 0x40, 0x40);
		return true;
	}
	return false;
}