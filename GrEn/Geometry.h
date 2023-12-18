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
	void setPos(const float x, const float y, const float z);
	void addPos(const float x, const float y, const float z);
	void getPos(GrEn::vec3<float>& vec) const;
	void setRotation(const float x, const float y, const float z);
	void addRotation(const float x, const float y, const float z);
	void getRotation(GrEn::vec3<float>& vec) const;
	void setScale(const float x, const float y, const float z);
	void setAdd(const float x, const float y, const float z);
	void getScale(GrEn::vec3<float>& vec) const;
	void getWorldMat(GrEn::mat4<float>& mat) const;
	//add ability to increase geometry length furthur

private:
	GrEn::Triangle* primitives;
	int bound;
	int iter;
	int available;
	GrEn::vec3<float> position;
	GrEn::vec3<float> scale;
	GrEn::vec3<float> rotation;
};

