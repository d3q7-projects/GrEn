#include "GrEn.h"
#include "GrEnDefinitions.h"
#include "Window.h"
#include "Camera.h"
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Timer.h"
#include "Rectangle.h"
#include "VectorMath.hpp"
#include "MatrixMath.hpp"
#include "Geometry.h"
#include "GeometryGroup.h"

static void draw() {
	GrEn::exception e = 0;
	Window window("ooly", e);
	Camera c(window, 90, { 0,0,0 }, { 0,0,1 }, Projection::Perspective);
	CHECK(e);


	Geometry triangulation;
	triangulation.addTrig({ { {0,0,2}, {1,0,2 }, {0,1,2} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {1,1,2}, {1,0,2 }, {0,1,2} }, {{0}, {0}, {0}} , {{0}, {0}} });

	triangulation.addTrig({ { {0,0,3}, {1,0,3 }, {0,1,3} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {1,1,3}, {1,0,3 }, {0,1,3} }, {{0}, {0}, {0}} , {{0}, {0}} });

	triangulation.addTrig({ { {1,1,2}, {1,0,3 }, {1,1,3} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {1,1,2}, {1,0,3 }, {1,0,2} }, {{0}, {0}, {0}} , {{0}, {0}} });

	triangulation.addTrig({ { {0,1,2}, {0,0,3 }, {0,1,3} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {0,1,2}, {0,0,3 }, {0,0,2} }, {{0}, {0}, {0}} , {{0}, {0}} });

	triangulation.addTrig({ { {1,1,2}, {0,1,3 }, {1,1,3} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {1,1,2}, {0,1,3 }, {0,1,2} }, {{0}, {0}, {0}} , {{0}, {0}} });

	triangulation.addTrig({ { {1,0,2}, {0,0,3 }, {1,0,3} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {1,0,2}, {0,0,3 }, {0,0,2} }, {{0}, {0}, {0}} , {{0}, {0}} });

	triangulation.setPos(-0.5, -0.5, 0);

	GrEn::hexColor color(0xff000000);
	GrEn::hexColor color2(0xffffff00);
	//fix them not blending properly
	Rectangle rect(100, 150, 300, 400, 0x40FF0000);
	Rectangle rect1(40, 200, 400, 300, 0x400000FF);
	Rectangle rect2(60, 300, 200, 300, 0x4000FF20);
	window.fill(color);

	float blueness = 0.0f;
	int num = 0;
	Timer t;
	while (!window.getStatus().quit)
	{
		if (!window.getStatus().quit)
		{
			window.fill(color);
			c.addGeometry(&triangulation);
			c.render();
			//window.draw(rect);
			//window.draw(rect1);
			//window.draw(rect2);
			window.update();
			double diff = t.tickAndReset();
			rect.setColor(rect.getColor().value + 1);
			num++;
			if (num % 100 == 0)
			{
				window.setTitle(std::to_string(1 / t.getAverage() * 1000));
			}
		}
	}
}

int main(int argc, char* args[])
{
	GrEn::exception e;
	CHECKFUNC(e, GrEn::initialize());
	
	draw();
	
	GrEn::finish();

	return 0;
}
