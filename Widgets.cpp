#include <string>
#include <algorithm>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Widgets.h"
#include "Core.h"

static void draw(SDL_Texture* texture, SDL_Rect& rect, SDL_FPoint& pivot)
{
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x -= static_cast<int>(rect.w * pivot.x);
	rect.y -= static_cast<int>(rect.h * pivot.y);
	SDL_RenderCopy(Core::renderer, texture, NULL, &rect);
}

void Widgets::setFont(std::string path, int size)
{
	if (font)
		TTF_CloseFont(font);
	font = TTF_OpenFont(path.c_str(), size);
}

void Widgets::label(std::string text, SDL_Point pos, SDL_Color color, SDL_FPoint pivot)
{
	SDL_Surface* surface{ TTF_RenderText_Blended(font, text.c_str(), color) };
	SDL_Texture* texture{ SDL_CreateTextureFromSurface(Core::renderer, surface) };
	SDL_Rect rect{ pos.x, pos.y };
	draw(texture, rect, pivot);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

bool Widgets::button(SDL_Texture* texture, SDL_Point pos, SDL_FPoint pivot)
{
	SDL_Rect rect{ pos.x, pos.y};
	draw(texture, rect, pivot);
	if (SDL_PointInRect(&Core::mouse, &rect))
	{
		SDL_SetTextureColorMod(texture, 0xa0, 0xa0, 0xa0);
		if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LEFT) && SDL_PointInRect(&Core::clickPos, &rect))
		{
			SDL_SetTextureColorMod(texture, 0x60, 0x60, 0x60);
			Core::clickPos = { 0, 0 };
			return true;
		}
	}
	else
		SDL_SetTextureColorMod(texture, 0xff, 0xff, 0xff);
	return false;
}

void Widgets::image(SDL_Texture* texture, SDL_Point pos, SDL_FPoint pivot)
{
	SDL_Rect rect{ pos.x, pos.y };
	draw(texture, rect, pivot);
}