#pragma once
#include "Geometry.h"
#include "GrEnException.h"

#define GEOMETRY_MAX 256

class GeometryGroup
{
public:
	GeometryGroup();
	GeometryGroup(Geometry** prims, const int len);
	~GeometryGroup();
	GrEn::exception addGeometry(Geometry*);
	int getLen() const;
	GrEn::exception removeGeometry(const int index);
	void resetIteration();
	GrEn::exception iterate(Geometry*& geometry);

private:
	Geometry** geometries;
	int bound;
	int iter;
	int available;
};
