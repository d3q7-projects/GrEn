#include "Window.h"
#define NO_EXCEP 0
#define SDL_WINDOW_CREATE_FAIL 2
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

Window::Window(GrEn::exception& e)
{
	this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
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

int Window::getHeight() 
{
	SDL_GetWindowSizeInPixels(this->window, &(this->width), &(this->height));
	return this->height;
}

int Window::getWidth()
{
	SDL_GetWindowSizeInPixels(this->window, &(this->width), &(this->height));
	return this->width;
}

void Window::setHeight(const int height)
{
	SDL_SetWindowSize(this->window, this->width, height);
}

void Window::setWidth(const int width)
{
	SDL_SetWindowSize(this->window, width, this->height);
}
