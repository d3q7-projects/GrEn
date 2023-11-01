#pragma once
#include <SDL.h>
#include "GrEnException.h"

enum class windowState
{
	floating,
	maximized,
	fullscreen
};

class Window
{
public:
	Window(GrEn::exception &e);
	//Window(const int width, const int height, GrEn::exception& e);
	//Window(const int width, const int height, const windowState state, GrEn::exception& e);
	int getHeight();
	int getWidth() ;
	void setHeight(const int height);
	void setWidth(const int width);
	GrEn::exception update();
	windowState getState() const;
	void setState(windowState state) const;
	
private:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	windowState state;
	int width;
	int height;
};

