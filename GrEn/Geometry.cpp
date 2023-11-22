#include "Geometry.h"
#define GREN_GEOMETRY_OOB 3

inline bool isNotNull(const GrEn::Triangle& t) { 
	return t.vertex[0].x ||
		t.vertex[0].y ||
		t.vertex[0].z ||
		t.vertex[1].x ||
		t.vertex[1].y ||
		t.vertex[1].z ||
		t.vertex[2].x ||
		t.vertex[2].y ||
		t.vertex[2].z;
}

Geometry::Geometry() : bound(0),available(0), primitives(), worldPosition(), rotation() { }

Geometry::Geometry(const GrEn::Triangle* prims, const int len) : bound(len), available(len), primitives(), worldPosition(), rotation()
{
	for (size_t i = 0; i < len; i++)
	{
		if (i >= MAX_PRIMS)
		{
			return;
		}
		if (isNotNull(prims[i]))
		{
			primitives[i] = prims[i];
		}
		else
		{
			this->bound--;
		}
	}
}

Geometry::Geometry(const std::string& file) : bound(0), available(0), primitives(), worldPosition(), rotation()
{
	_CRT_WARNING_MESSAGE("1", "This function isn't implemented yet");
	//TODO: implement file object extraction
}

GrEn::exception Geometry::addTrig(const GrEn::Triangle& prim)
{
	if(this->bound == MAX_PRIMS){
		return GrEn::exception(GREN_GEOMETRY_OOB);
	}
	this->primitives[this->available] = prim;
	for (size_t i = this->available; i < this->bound; i++)
	{
		if (!isNotNull(this->primitives[i]))
		{
			this->available = i;
			return;
		}
	}
	this->available = this->bound++;
}

int Geometry::getLen() const
{
	int len = 0;
	for (size_t i = this->available; i < this->bound; i++)
	{
		if (!isNotNull(this->primitives[i]))
		{
			len++;
		}
	}
	return len;
}

GrEn::exception Geometry::removeTrig(const int index)
{
	if (this->bound < MAX_PRIMS)
	{
		this->primitives[index].vertex[0] = { 0 };
		this->primitives[index].vertex[1] = { 0 };
		this->primitives[index].vertex[2] = { 0 };
		
		this->available = index < this->available ? index : this->available;
		return 0;
	}
	return GrEn::exception(GREN_GEOMETRY_OOB);
}
