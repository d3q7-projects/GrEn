#pragma once
#include <SDL.h>
#include <string>
#include "GrEnException.h"
#include "GrEnDefinitions.h"
#include "Shape2D.h"
#include <map>

enum class windowState
{
	floating,
	maximized,
	fullscreen,
	unknown
};

class Window;

struct windowEvent
{
	Window* quit;
	Window* maximize;
	Window* minimize;
	Window* resized;
	Window* focused;
	Window* unfocused;
	Window* clicked;
};

class Window
{
public:
	Window(const std::string& name, GrEn::exception &e);
	//TODO: (priority: 2) add more constructors
	//Window(const int width, const int height, GrEn::exception& e);
	//Window(const int width, const int height, const windowState state, GrEn::exception& e);
	~Window();

	static windowEvent getEvents();
	int getHeight();
	int getWidth();
	void setHeight(const int height);
	void setWidth(const int width);
	windowState getState() const;
	void setState(const windowState state) const;
	std::string getTitle() const;
	void setTitle(const std::string title);
	void draw(const Shape2D& shape);

	//This function doesn't have to be called as it is called by the destructor
	void destroy();
	void update();

	void fill(GrEn::rgba color);
	void fill(GrEn::hexColor color);
	
private:
	static std::map<void*, Window*> windowAssociation;
	void* window;
	void* windowFrame;
	void* windowFrameExtras;
	windowState state;
	int width;
	int height;
};

