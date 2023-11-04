#include "GrEn.h"
#include "SDL.h"
#define SDL_INIT_FAIL 1

GrEn::exception GrEn::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return SDL_INIT_FAIL;
	}
	return 0;
}

void GrEn::finish()
{
	SDL_Quit();
}
