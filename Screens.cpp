#include <algorithm>

#include <SDL_image.h>

#include "Core.h"
#include "Screens.h"
#include "Widgets.h"

void HomeScreen::draw() const
{
	SDL_Texture* texture{ IMG_LoadTexture(Core::renderer, "img/title.png") };
	int w{};
	int h{};
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_FRect rect{ Core::monitor.w * 0.5f, 0 };
	rect.w = std::clamp(static_cast<float>(w), Core::monitor.w * 0.1f, Core::monitor.w * 0.5f);
	rect.h = std::clamp(static_cast<float>(h), Core::monitor.h * 0.1f, Core::monitor.h * 0.5f);
	rect.x -= rect.w / 2;
	SDL_RenderCopyF(Core::renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}