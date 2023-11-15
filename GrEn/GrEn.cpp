#include "GrEn.h"
#include "SDL.h"
#include <thread>
#include <iostream>
#define SDL_INIT_FAIL 1

void manageWindowEvents() {
	while (true)
	{
	}

	std::cout << "myef\n";
}

GrEn::exception GrEn::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return SDL_INIT_FAIL;
	}
	//std::thread windowManager(manageWindowEvents);
	//windowManager.detach();
	return 0;
}

void GrEn::finish()
{
	SDL_Quit();
}
