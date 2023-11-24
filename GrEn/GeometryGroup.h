#pragma once
#include "Geometry.h"
#include "GrEnException.h"

#define GEOMETRY_MAX 128

class GeometryGroup
{
public:
	GeometryGroup();
	GeometryGroup(const Geometry** prims, const int len);
	~GeometryGroup();
	GrEn::exception addGeometry(const Geometry*);
	int getLen() const;
	GrEn::exception removeGeometry(const int index);
	void resetIteration();
	GrEn::exception iterate(const Geometry*& geometry);

private:
	const Geometry** geometries;
	int bound;
	int iter;
	int available;
};
