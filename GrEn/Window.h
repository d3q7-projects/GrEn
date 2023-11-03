#pragma once
#include <SDL.h>
#include <string>
#include "GrEnException.h"

enum class windowState
{
	floating,
	maximized,
	fullscreen,
	unknown
};

enum class windowEvent
{
	quit,
	//TODO: the following
	maximize,
	minimize,
	resized,
	focused,
	unfocused,
	clicked,
	none
};

class Window
{
public:
	~Window();
	Window(const std::string& name, GrEn::exception &e);
	//Window(const int width, const int height, GrEn::exception& e);
	//Window(const int width, const int height, const windowState state, GrEn::exception& e);
	int getHeight();
	int getWidth() ;
	void setHeight(const int height);
	void setWidth(const int width);
	//This function doesn't have to be called as it is called by the destructor
	void destroy();
	windowEvent update();
	windowState getState() const;
	void setState(windowState state) const;
	
private:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	windowState state;
	int width;
	int height;
};

