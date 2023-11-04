#include "GrEn.h"
#include "GrEnDefinitions.h"
#include "Window.h"
#include <SDL.h>
#include <iostream>


void draw() {
	GrEn::exception e;
	Window window("ooly", e);
	CHECK(e);
	window.fill({ 0, 1, 0, 1 });
	Window window2("ooly2", e);
	CHECK(e);

	bool first = true;
	bool second = true;
	while (first || second)
	{
		windowEvent events = Window::getEvents();
		if (first && events.quit == &window)
		{
			first = false;
			window.destroy();
		}
		else
		{
			window.update();
		}

		if (second && events.quit == &window2)
		{
			second = false;
			window2.destroy();
		}
		else
		{
			window2.update();
		}
	}
}

int main(int argc, char* args[])
{
	GrEn::exception e;
	CHECKFUNC(e, GrEn::initialize());
	std::cout << std::hex << GrEn::rgbaToHex({0.2 , 0.2, 0.2, 0}) << std::endl;

	draw();
	
	GrEn::finish();

	return 0;
}
