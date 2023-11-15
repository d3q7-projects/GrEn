#include "Window.h"
#define NO_EXCEP 0
#define SDL_WINDOW_CREATE_FAIL 2
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

std::map<void*, Window*> Window::windowManager;

Window::Window(const std::string& name, GrEn::exception& e) : window(0)
{

	this->windowFrame = SDL_GetWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	this->width = DEFAULT_WIDTH;
	this->height = DEFAULT_HEIGHT;
	this->state = windowState::maximized;
	this->title = name;
	this->status = { 0 };
	this->windowFrameExtras = new struct frameExtra[4096 * 4096];
	this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
	Window::windowManager[this->window] = this;
	e = window ? NO_EXCEP : SDL_WINDOW_CREATE_FAIL;
	
}

Window::~Window()
{
	if (this->window)
	{
		SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(this->window));
	}
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

windowEvent& Window::getStatus()
{
	return this->status;
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
	this->window = nullptr;
}

void Window::update()
{
	SDL_UpdateWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	this->status = { 0 };
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) { // stays same thread because of window
		if (sdlEvent.type == SDL_WINDOWEVENT) {
			Window* eventWindow = Window::windowManager[SDL_GetWindowFromID(sdlEvent.window.windowID)];
			if (!eventWindow)
			{
				continue;
			}
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
	if (this->window)
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

}

std::string Window::getTitle()
{
	if (this->window)
	{
		this->title = SDL_GetWindowTitle(reinterpret_cast<SDL_Window*>(this->window));
	}
	return this->title;
}

void Window::setTitle(const std::string title)
{
	SDL_SetWindowTitle(reinterpret_cast<SDL_Window*>(this->window), title.c_str());
}

void Window::draw(const Shape2D& shape)
{
	this->windowFrame = SDL_GetWindowSurface(reinterpret_cast<SDL_Window*>(this->window));
	shape.draw(reinterpret_cast<SDL_Surface*>(this->windowFrame)->pixels, this->windowFrameExtras, this->getWidth(), this->getHeight());
}

