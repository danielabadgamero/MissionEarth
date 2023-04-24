#include <algorithm>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "ControlRoom.h"
#include "Core.h"
#include "Planet.h"
#include "Widgets.h"
#include "Screens.h"

ControlRoom::ControlRoom()
{
	buttons["map"] = IMG_LoadTexture(Core::renderer, "img/mapButton.png");
	buttons["vessel"] = IMG_LoadTexture(Core::renderer, "img/vesselButton.png");

	topPanelTexture = IMG_LoadTexture(Core::renderer, "img/topPanelInfo.png");
}

void ControlRoom::draw() const
{
	Widgets::image(Core::getScreen<GameScreen*>(Core::game)->getSOI()->getIcon(), { Core::monitor.w / 3, Core::monitor.h / 2 }, { 0.5, 0.5 });
	Widgets::image(topPanelTexture, { Core::monitor.w / 2, 0 }, { 0.5, 0 });

	std::string SOIname{ Core::getScreen<GameScreen*>(Core::game)->getSOI()->getID().c_str() };
	SOIname[0] -= 0x20;
	Widgets::setFont("C:\\Windows\\Fonts\\AGENCYB.TTF", 50);
	Widgets::label(SOIname, { Core::monitor.w / 2, 0 }, { 0x28, 0x00, 0xbe }, { 0.5, 0 });

	if (Widgets::button(buttons.at("map"), { Core::monitor.w / 2, Core::monitor.h / 3 }, { 0, 0.5 }))
		Core::getScreen<GameScreen*>(Core::game)->getView() = GameScreen::View::map;

	if (Widgets::button(buttons.at("vessel"), { Core::monitor.w / 2, Core::monitor.h / 3 + 200 }, { 0, 0.5 }))
		Core::getScreen<GameScreen*>(Core::game)->getView() = GameScreen::View::vessel;
}