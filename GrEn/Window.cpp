#include "Window.h"
#define NO_EXCEP 0
#define SDL_WINDOW_CREATE_FAIL 2
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

std::map<void*, Window*> Window::windowAssociation;

Window::Window(const std::string& name, GrEn::exception& e)
{
	this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
	e = window ? NO_EXCEP : SDL_WINDOW_CREATE_FAIL;

	this->windowFrame = SDL_GetWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	this->width = DEFAULT_WIDTH;
	this->height = DEFAULT_WIDTH;
	this->state = windowState::maximized;
	Window::windowAssociation[this->window] = this;
}

Window::~Window()
{
	if (this->window)
	{
		SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(this->window));
	}
}

windowEvent Window::getEvents()
{
	SDL_Event sdlEvent;
	windowEvent event = { 0 };
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_WINDOWEVENT) {
			if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
				event.quit = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}
			if (sdlEvent.window.event == SDL_WINDOWEVENT_MINIMIZED) {
				event.minimize = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}
			if (sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
				event.focused = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}
			if (sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
				event.unfocused = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}
			if (sdlEvent.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				event.maximize = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}
			if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				event.resized = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}
			if (sdlEvent.window.event == SDL_WINDOWEVENT_HIT_TEST) {
				event.clicked = windowAssociation[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			}

		}
	}

	return event;
}

int Window::getHeight()
{
	if (this->window){
		SDL_GetWindowSizeInPixels(reinterpret_cast<SDL_Window*>(this->window), &(this->width), &(this->height));
	}
	return this->height;
}

int Window::getWidth() 
{
	if (this->window){
		SDL_GetWindowSizeInPixels(reinterpret_cast<SDL_Window*>(this->window), &(this->width), &(this->height));
	}
	return this->width;
}

void Window::setHeight(const int height)
{
	if (this->window){
		SDL_SetWindowSize(reinterpret_cast<SDL_Window*>(this->window), this->width, height);
	}
	this->height = height;
}

void Window::setWidth(const int width)
{
	if (this->window){
		SDL_SetWindowSize(reinterpret_cast<SDL_Window*>(this->window), width, this->height);
	}
	this->width = width;
}

void Window::destroy(){
	if (this->window) {
		SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(this->window));
	}
}

void Window::update()
{
	SDL_UpdateWindowSurface(reinterpret_cast<SDL_Window*>(this->window));

}

void Window::fill(GrEn::rgba color)
{
	this->windowFrame = SDL_GetWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	SDL_FillRect(reinterpret_cast<SDL_Surface*>(this->windowFrame), NULL, GrEn::rgbaToHex(color).value);
}
void Window::fill(GrEn::hexColor color)
{
	this->windowFrame = SDL_GetWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	SDL_FillRect(reinterpret_cast<SDL_Surface*>(this->windowFrame), NULL, color.value);
}

windowState Window::getState() const
{
	switch (SDL_GetWindowFlags(reinterpret_cast<SDL_Window*>(this->window)))
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

void Window::setState(const windowState state) const
{
	switch (state)
	{
	case windowState::floating:
		SDL_SetWindowFullscreen(reinterpret_cast<SDL_Window*>(this->window), 0);
		SDL_RestoreWindow(reinterpret_cast<SDL_Window*>(this->window));
		break;
	case windowState::maximized:
		SDL_SetWindowFullscreen(reinterpret_cast<SDL_Window*>(this->window), 0);
		SDL_MaximizeWindow(reinterpret_cast<SDL_Window*>(this->window));
		break;
	case windowState::fullscreen:
		SDL_SetWindowFullscreen(reinterpret_cast<SDL_Window*>(this->window), SDL_WINDOW_FULLSCREEN);
		break;
	default:
		break;
	}
}

std::string Window::getTitle() const
{
	return SDL_GetWindowTitle(reinterpret_cast<SDL_Window*>(this->window));
}

void Window::setTitle(const std::string title)
{
	SDL_SetWindowTitle(reinterpret_cast<SDL_Window*>(this->window), title.c_str());
}

void Window::draw(const Shape2D& shape)
{
	this->windowFrame = SDL_GetWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	shape.draw(this->windowFrame, this->windowFrameExtras, this->width, this->height);
}

