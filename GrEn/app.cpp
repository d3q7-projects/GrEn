#include "GrEn.h"
#include "GrEnDefinitions.h"
#include "Window.h"
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Timer.h"
#include "Rectangle.h"

void draw() {
	GrEn::exception e = 0;
	Window window("ooly", e);
	Window window2("ooly2", e);
	CHECK(e);

	GrEn::hexColor color(0x00000000);
	GrEn::hexColor color2(0xffffff00);
	//fix them not blending properly
	Rectangle rect(100, 150, 300, 400, 0x60FF0000);
	Rectangle rect1(40, 200, 400, 300, 0xF00000FF);
	Rectangle rect2(60, 300, 200, 300, 0x6000FF20);
	window.fill(color);

	float blueness = 0.0f;
	int num = 0;
	Timer t; 
	while (!(window.getStatus().quit && window2.getStatus().quit))
	{
		if (!window.getStatus().quit)
		{
			window.fill(color);
			window.draw(rect1);
			window.draw(rect2);
			window.draw(rect);
			window.update();
			double diff = t.tickAndReset();
			rect.setColor(rect.getColor().value + 1);
			num++;
			if (num % 100 == 0)
			{
				window.setTitle(std::to_string(1 / t.getAverage() * 1000));
			}
		}
		if (!window2.getStatus().quit)
		{
			window2.fill(color2);
			window2.update();
		}
	}
}

int main(int argc, char* args[])
{
	GrEn::exception e;
	CHECKFUNC(e, GrEn::initialize());
	std::cout << std::hex << GrEn::rgbaToHex({0.2f , 0.2f, 0.2f, 0.0f}).value << std::endl;

	draw();
	
	GrEn::finish();

	return 0;
}
