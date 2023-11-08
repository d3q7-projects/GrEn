#pragma once
#include "Shape2D.h"
#include "GrEnDefinitions.h"

class Rectangle :
    public Shape2D
{
public:
    Rectangle(int x, int y, int width, int length, GrEn::hexColor color);
    void setX(const int x);
    void setY(const int y);
    void setWidth(const int width);
    void setHeight(const int length);
    void setColor(const GrEn::hexColor color);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    GrEn::hexColor getColor() const;
    virtual void draw(void* frame, void* frameExtras, const int width, const int height) const override;

private:
    int x;
    int y;
    int width;
    int height;
    GrEn::hexColor color;

};

