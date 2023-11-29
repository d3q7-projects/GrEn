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
	Geometry triangulation2;
	Geometry triangulation3;
	GeometryGroup gg;
	triangulation.addTrig({ { {-1,0,0}, {1,0,0 }, {0,1.41,0} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {-3,2,-2}, {1,4,0 }, {1,2.41,-4} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {-3,2,-3}, {2,4,-1 }, {3,4.41,-1} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.removeTrig(2);
	triangulation.addTrig({ { {-1,0,0}, {1,0,0 }, {0,1.41,0} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.removeTrig(0);
	triangulation.removeTrig(1);
	triangulation.getLen();
	triangulation.addTrig({ { {-3,2,-2}, {1,4,0 }, {1,2.41,-4} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {-3,2,-3}, {2,4,-1 }, {3,4.41,-1} }, {{0}, {0}, {0}} , {{0}, {0}} });
	triangulation.addTrig({ { {-3,2,-3}, {2,4,-1 }, {3,4.41,-1} }, {{0}, {0}, {0}} , {{0}, {0}} });

	gg.addGeometry(&triangulation);
	gg.addGeometry(&triangulation2);
	gg.addGeometry(&triangulation3);
	gg.removeGeometry(2);
	gg.addGeometry(&triangulation);
	gg.removeGeometry(0);
	gg.removeGeometry(1);
	gg.getLen();
	gg.addGeometry(&triangulation);


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
		c.addGeometryGroup(&gg);
		c.render();
		GrEn::mat3<float> mat = { {1, -1,  2},
									{-2, 3, -4},
									{9,  3,  1} };
		GrEn::mat3<float> mat2 = { {-15.0f / 17.0f, -7.0f / 17.0f, 2.0f / 17.0f},
									{2,  1,  0},
									{33.0f / 17.0f, 12.0f / 17.0f, -1.0f / 17.0f} };
		GrEn::mat3<float> mat3 = { 0 };
		matMult(mat, mat2, mat3);
		if (!window.getStatus().quit)
		{
			window.fill(color);
			window.draw(rect);
			window.draw(rect1);
			window.draw(rect2);
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
