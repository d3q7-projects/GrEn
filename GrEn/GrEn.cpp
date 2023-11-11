#include "GrEn.h"
#include "SDL.h"
#include "windowManager.h"
#include <thread>
#define SDL_INIT_FAIL 1

void manageWindowEvents() {
	SDL_Event sdlEvent;
	while (true)
	{
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_WINDOWEVENT) {
				Window* eventWindow = windowManager::getWindow(SDL_GetWindowFromID(sdlEvent.window.windowID));
				windowEvent& status = eventWindow->getStatus();
				if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
					eventWindow->destroy();
					status.quit = true;
				}
				if (sdlEvent.window.event == SDL_WINDOWEVENT_MINIMIZED) {
					status.minimize = true;
				}
				if (sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
					status.focused = true;
				}
				if (sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
					status.unfocused = true;
				}
				if (sdlEvent.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
					status.maximize = true;
				}
				if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					status.resized = true;
				}
				if (sdlEvent.window.event == SDL_WINDOWEVENT_HIT_TEST) {
					status.clicked = true;
				}

			}
		}
	}
}

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
