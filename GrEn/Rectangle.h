#pragma once
#include "Shape2D.h"
#include "GrEnDefinitions.h"

class Rectangle :
    public Shape2D
{
public:
    Rectangle(int x, int y, int width, int length, GrEn::rgba color);
    void setX(const int x);
    void setY(const int y);
    void setWidth(const int width);
    void setLength(const int length);
    void setColor(const GrEn::rgba color);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getLength() const;
    GrEn::rgba getColor() const;
    virtual void draw(void* frame, void* frameExtras) const override;

private:
    int x;
    int y;
    int width;
    int length;
    GrEn::rgba color;

};

