#include "GrEn.h"
#include "Window.h"
#include <SDL.h>
#include <iostream>


void draw() {
	GrEn::exception e;
	Window window("ooly", e);
	CHECK(e, GrEn::initialize());
	Window window2("ooly2", e);
	CHECK(e, GrEn::initialize());
	bool first = true;
	bool second = true;
	while (first || second)
	{
		if (first && window.update() == windowEvent::quit)
		{
			first = false;
			window.destroy();
		}
		if (second && window2.update() == windowEvent::quit)
		{
			second = false;
			window2.destroy();
		}
	}
}

int main(int argc, char* args[])
{
	GrEn::exception e;
	CHECK(e, GrEn::initialize());
	
	draw();
	
	GrEn::finish();

	return 0;
}
