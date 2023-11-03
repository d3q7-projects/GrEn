#include "Window.h"
#define NO_EXCEP 0
#define SDL_WINDOW_CREATE_FAIL 2
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

Window::Window(const std::string& name, GrEn::exception& e)
{
	this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		e = SDL_WINDOW_CREATE_FAIL;
	}
	else {
		e = NO_EXCEP;
	}
	this->width = DEFAULT_WIDTH;
	this->height = DEFAULT_WIDTH;
	this->state = windowState::maximized;
}

Window::~Window()
{
	if (this->window)
	{
		SDL_DestroyWindow(this->window);
	}
}

int Window::getHeight() 
{
	if (this->window){
		SDL_GetWindowSizeInPixels(this->window, &(this->width), &(this->height));
	}
	return this->height;
}

int Window::getWidth()
{
	if (this->window){
		SDL_GetWindowSizeInPixels(this->window, &(this->width), &(this->height));
	}
	return this->width;
}

void Window::setHeight(const int height)
{
	if (this->window){
		SDL_SetWindowSize(this->window, this->width, height);
	}
	this->height = height;
}

void Window::setWidth(const int width)
{
	if (this->window){
		SDL_SetWindowSize(this->window, width, this->height);
	}
	this->width = width;
}

void Window::destroy(){
	if (this->window) {
		SDL_DestroyWindow(this->window);
	}
}

windowEvent Window::update()
{
	SDL_UpdateWindowSurface(window);

	SDL_Event sdlEvent;
	windowEvent event = windowEvent::none;
	bool quit = false;
	while (SDL_PollEvent(&sdlEvent)){
		if (sdlEvent.type == SDL_WINDOWEVENT) {
			if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
				event = windowEvent::quit;
			}
		}
	}
	
	return event;
}

windowState Window::getState() const
{
	switch (SDL_GetWindowFlags(this->window))
	{
	case SDL_WINDOW_FULLSCREEN:
		return windowState::fullscreen;
	case SDL_WINDOW_MAXIMIZED:
		return windowState::maximized;
	case !SDL_WINDOW_MINIMIZED:
		return windowState::floating;
	default:
		return windowState::unknown;
	}
}

void Window::setState(windowState state) const
{
	switch (state)
	{
	case windowState::floating:
		SDL_SetWindowFullscreen(this->window, 0);
		SDL_RestoreWindow(this->window);
		break;
	case windowState::maximized:
		SDL_SetWindowFullscreen(this->window, 0);
		SDL_MaximizeWindow(this->window);
		break;
	case windowState::fullscreen:
		SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
		break;
	default:
		break;
	}
}
