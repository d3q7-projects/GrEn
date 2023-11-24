#include "GrEnException.h"
#define NO_EXCEP 0
#define SDL_INIT_FAIL 1
#define SDL_WINDOW_CREATE_FAIL 2
#define GREN_OOB 3


const char* GrEn::translateExcep(const exception e)
{
	switch (e)
	{
	case NO_EXCEP:
		return "No Exception";
	case SDL_INIT_FAIL:
		return "The SDL library couldn't initialize correctly";
	case SDL_WINDOW_CREATE_FAIL:
		return "Failed to create a window with the SDL library";
	case GREN_OOB:
		return "The geometry has reached its maxed capacity";
	default:
		return "Unresolved Exception";
	}
}