#pragma once
#include "GrEnDefinitions.h"
#include "GrEnException.h"
#include <string>

#define MAX_PRIMS 1024

class Geometry
{
public:
	Geometry();
	Geometry(const GrEn::Triangle* prims, const int len);
	Geometry(const std::string& file);
	GrEn::exception addTrig(const GrEn::Triangle&);
	int getLen() const;
	GrEn::exception removeTrig(const int index);

private:
	GrEn::Triangle primitives[MAX_PRIMS];
	int bound;
	int available;
	GrEn::mat4<float> worldPosition;
	GrEn::vec3<float> rotation;
};

