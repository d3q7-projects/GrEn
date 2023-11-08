#include "Rectangle.h"

void Rectangle::draw(void* frame, void* frameExtras) const
{
	unsigned int* unraveledFrame = reinterpret_cast<unsigned int*>(frame);

}

Rectangle::Rectangle(int x, int y, int width, int length, GrEn::rgba color) : x(x), y(y), width(width), length(length), color(color)
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

void Rectangle::setLength(const int length)
{
	this->length = length;
}

void Rectangle::setColor(const GrEn::rgba color)
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

int Rectangle::getLength() const
{
	return this->length;
}

GrEn::rgba Rectangle::getColor() const
{
	return this->color;
}
