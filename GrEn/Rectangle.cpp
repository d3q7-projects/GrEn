#include "Rectangle.h"
#include "SDL.h"
#include "GrEnColors.h"
#include <string.h>

void Rectangle::draw(void* frame, void* frameExtras, const int width, const int height) const
{
	GrEn::hexColor* unraveledFrame = reinterpret_cast<GrEn::hexColor*>(frame);
	
	const int heightBoundClamped = this->y + this->height >= height ? height : (this->y + this->height < 0 ? 0 : this->y + this->height);
	const int widthClamped = this->x + this->width >= width ? width - this->x : (this->x + this->width < 0 ? 0 : this->width);
	for (int j = this->y; j < heightBoundClamped; j++)
	{
		for (int i = this->x; i < this->x + widthClamped; i++)
		{
			*(unraveledFrame + i + width * j) = GrEn::aOverBhex(this->color, unraveledFrame[i + width * j]);
		}
		
	}
}

Rectangle::Rectangle(int x, int y, int width, int height, GrEn::hexColor color) : x(x), y(y), width(width), height(height), color(color)
{
}

void Rectangle::setX(const int x)
{
	this->x = x;
}

void Rectangle::setY(const int y)
{
	this->y = y;
}

void Rectangle::setWidth(const int width)
{
	this->width = width;
}

void Rectangle::setHeight(const int height)
{
	this->height = height;
}

void Rectangle::setColor(const GrEn::hexColor color)
{
	this->color = color;
}

int Rectangle::getX() const
{
	return this->x;
}

int Rectangle::getY() const
{
	return this->y;
}

int Rectangle::getWidth() const
{
	return this->width;
}

int Rectangle::getHeight() const
{
	return this->height;
}

GrEn::hexColor Rectangle::getColor() const
{
	return this->color;
}
