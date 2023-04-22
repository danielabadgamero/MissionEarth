#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "Core.h"
#include "Level.h"
#include "Screens.h"

Level::Level(std::string name) : id{ name }
{
	icon = IMG_LoadTexture(Core::renderer, ("img/planets/" + name + ".png").c_str());
}

void Level::loadInfo()
{
	socket = SDLNet_TCP_Open(&ip);

	std::string request{ "GET /v1/planets?name=" + id + " HTTP/1.1\nHost: api.api-ninjas.com\nX-Api-Key: TMq4LqmQ7WKxZcPVPzktwQ==wt63e5UYmYfJqcPZ\n\n" };
	SDLNet_TCP_Send(socket, request.c_str(), static_cast<int>(request.size()));
	std::string response{ '\0' };
	char c{};
	while (SDLNet_TCP_Recv(socket, &c, 1) == 1)
	{
		std::cout << c;
		response.push_back('\0');
	}

	SDL_Log(response.c_str());

	SDLNet_TCP_Close(socket);
}