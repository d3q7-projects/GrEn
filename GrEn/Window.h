#pragma once
#include <SDL.h>
#include <string>
#include "GrEnException.h"
#include "GrEnDefinitions.h"
#include "Shape2D.h"

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
	bool quit;
	bool maximize;
	bool minimize;
	bool resized;
	bool focused;
	bool unfocused;
	bool clicked;
};

struct frameExtra
{
	int z;
};

class Window
{
public:
	Window(const std::string& name, GrEn::exception &e);
	//TODO: (priority: 2) add more constructors
	//Window(const int width, const int height, GrEn::exception& e);
	//Window(const int width, const int height, const windowState state, GrEn::exception& e);
	~Window();

	int getHeight();
	int getWidth();
	windowEvent& getStatus();
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
	void* window;
	void* windowFrame;
	struct frameExtra windowFrameExtras[5000][5000];
	windowState state;
	struct windowEvent status;
	int width;
	int height;
};

