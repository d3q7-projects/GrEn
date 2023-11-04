#include "GrEn.h"
#include "GrEnDefinitions.h"
#include "Window.h"
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Timer.h"


void draw() {
	GrEn::exception e;
	Window window("ooly", e);
	CHECK(e);
	window.fill({ 0, 1, 0, 1 });

	bool first = true;
	int num = 0;
	Timer t; 
	while (first)
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
		double diff = t.tickAndReset();
		num++;
		if (num % 1 == 0)
		{
			std::cout << 1/t.getAverage()*1000 << std::endl;
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
