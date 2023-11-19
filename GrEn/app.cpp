#include "GrEn.h"
#include "GrEnDefinitions.h"
#include "Window.h"
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Timer.h"
#include "Rectangle.h"
#include "VectorMath.hpp"
#include "MatrixMath.hpp"

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
		GrEn::mat3<float> mat = { {1, -1,  2},
									{-2, 3, -4},
									{9,  3,  1} };
		GrEn::mat3<float> mat2 = { {-15.0f / 17.0f, -7.0f / 17.0f, 2.0f / 17.0f},
									{2,  1,  0},
									{33.0f / 17.0f, 12.0f / 17.0f, -1.0 / 17.0} };
		GrEn::mat3<float> mat3 = { 0 };
		matMult(mat, mat2, mat3);
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
	struct GrEn::vec3<float> x = { 1.0f,0.0f,1.0f };
	struct GrEn::vec3<float> y = { 0.0f,1.0f,1.0f };
	struct GrEn::vec3<float> z = { 0.0f,0.0f,0.0f };
	vecCrossProd(x, y, z);
	vecNormalize(z);
	std::cout << "(" << z.x << "," << z.y << "," << z.z << ") -> " << vecLen(z) << std::endl;

	GrEn::mat3<float> mat = {	{-3, 2, -5},
								{-1, 0, -2},
								{3, -4,  1} };
	GrEn::mat3<float> mat2 = { {-15.0f / 17.0f, -7.0f / 17.0f, 2.0f / 17.0f},
								{2,  1,  0},
								{33.0f / 17.0f, 12.0f / 17.0f, -1.0f / 17.0f} };
	GrEn::mat3<float> mat3 = {0};
	matMult(mat, mat2, mat3);
	
	matPrint(mat);
	std::cout << "*" << std::endl;
	matPrint(mat2);
	std::cout << "=" << std::endl;
	matPrint(mat3);

	std::cout << std::endl << std::endl;

	matVecMult(mat, z, x);
	matPrint(mat);
	std::cout << "*" << std::endl;
	vecPrint(z);
	std::cout << "=" << std::endl;
	vecPrint(x);

	std::cout << std::endl << std::endl;

	matGetAdjunt(mat, mat3);

	matPrint(mat);
	std::cout << "^adj" << std::endl;
	std::cout << "=" << std::endl;
	matPrint(mat3);

	std::cout << std::endl << std::endl;

	matGetInverse(mat, mat3);

	matPrint(mat);
	std::cout << "^-1" << std::endl;
	std::cout << "=" << std::endl;
	matPrint(mat3);

	std::cout << std::endl << std::endl;

	matMult(mat, mat3, mat2);

	matPrint(mat);
	std::cout << "*" << std::endl;
	matPrint(mat3);
	std::cout << "=" << std::endl;
	matPrint(mat2);


	std::cout << std::endl << std::endl << "|mat1| = " << matDeterminent(mat) << std::endl;
	
	draw();
	
	GrEn::finish();

	return 0;
}
