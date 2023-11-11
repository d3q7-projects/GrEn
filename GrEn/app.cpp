#include "GrEn.h"
#include "GrEnDefinitions.h"
#include "Window.h"
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Timer.h"
#include "Rectangle.h"

void draw() {
	GrEn::exception e;
	Window window("ooly", e);
	CHECK(e);

	GrEn::hexColor color(0x00000000);
	//fix them not blending properly
	Rectangle rect(100, 150, 300, 400 , 0x60FF0000);
	Rectangle rect1(40, 200, 400, 300, 0xF00000FF);
	Rectangle rect2(60, 300, 200, 300, 0x6000FF20);
	window.fill(color);

	float blueness = 0.0f;
	bool first = true;
	int num = 0;
	Timer t; 
	while (first)
	{
		if (first && window.getStatus().quit)
		{
			first = false;
			window.destroy();
		}
		else
		{
			window.fill(color);
			window.draw(rect1);
			window.draw(rect2);
			window.draw(rect);
			window.update();
		}
		double diff = t.tickAndReset();
		blueness += 0.001f;
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
	std::cout << std::hex << GrEn::rgbaToHex({0.2f , 0.2f, 0.2f, 0.0f}).value << std::endl;

	draw();
	
	GrEn::finish();

	return 0;
}
