#pragma once
#include <string>
#include <map>
#include "GrEnException.h"
#include "GrEnDefinitions.h"
#include "Shape2D.h"
#include "Camera.h"

enum class windowState
{
	floating,
	maximized,
	fullscreen,
	unknown
};

struct windowEvent
{
	bool quit = false;
	bool maximize = false;
	bool minimize = false;
	bool resized = false;
	bool focused = false;
	bool unfocused = false;
	bool clicked = false;
};

struct frameExtra
{
	float z;
};

class Camera;
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
	std::string getTitle();
	void setTitle(const std::string title);
	void draw(const Shape2D& shape);

	//This function doesn't have to be called as it is called by the destructor
	void destroy();
	void update();

	void fill(GrEn::rgba color);
	void fill(GrEn::hexColor color);
	
private:
	static std::map<void*, Window*> windowManager; //internal use
	void* window;
	void* windowFrame;
	struct frameExtra* windowFrameExtras;
	windowState state;
	struct windowEvent status;
	std::string title;
	int width;
	int height;

	friend class Camera;
};

