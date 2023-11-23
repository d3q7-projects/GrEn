#pragma once
#include "GrEnDefinitions.h"
#include "GrEnException.h"
#include <string>

#define MAX_PRIMS 1024
#define GEOMETRY_END -1
#define GEOMETRY_BEGIN 0

class Geometry
{
public:
	Geometry();
	Geometry(const GrEn::Triangle* prims, const int len);
	Geometry(const std::string& file);
	~Geometry();
	GrEn::exception addTrig(const GrEn::Triangle&);
	int getLen() const;
	GrEn::exception removeTrig(const int index);
	void resetIteration();
	GrEn::exception iterate(GrEn::Triangle& prim);

private:
	GrEn::Triangle* primitives;
	int bound;
	int iter;
	int available;
	GrEn::mat4<float> worldPosition;
	GrEn::vec3<float> rotation;
};

