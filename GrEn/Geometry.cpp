#include "Geometry.h"
#define GREN_OOB 3

//TODO: seems that both Geometry and Geometry group have the same structure so i might as well turn it to an abstract class

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

Geometry::Geometry() : bound(0), iter(0), available(0), primitives(new GrEn::Triangle[MAX_PRIMS]), worldPosition(), rotation() { }

Geometry::Geometry(const GrEn::Triangle* prims, const int len) : bound(len), iter(0), available(len), primitives(new GrEn::Triangle[MAX_PRIMS]), worldPosition(), rotation()
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

Geometry::Geometry(const std::string& file) : bound(0), iter(0), available(0), primitives(new GrEn::Triangle[MAX_PRIMS]), worldPosition(), rotation()
{
	_CRT_WARNING_MESSAGE("1", "This function isn't implemented yet");
	//TODO: implement file object extraction
}

Geometry::~Geometry()
{
	delete[] this->primitives;
}

GrEn::exception Geometry::addTrig(const GrEn::Triangle& prim)
{
	if(this->bound == MAX_PRIMS){
		return GrEn::exception(GREN_OOB);
	}
	this->primitives[this->available] = prim;
	for (int i = this->available; i < this->bound; i++)
	{
		if (!isNotNull(this->primitives[i]))
		{
			this->available = i;
			return 0;
		}
	}
	this->available = this->available == this->bound ? ++this->bound : this->bound;
	return 0;
}

int Geometry::getLen() const
{
	int len = this->available;
	for (size_t i = this->available; i < this->bound; i++)
	{
		if (isNotNull(this->primitives[i]))
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
		this->bound = this->bound - 1 == index ? index : this->bound;
		return 0;
	}
	return GrEn::exception(GREN_OOB);
}

void Geometry::resetIteration()
{
	this->iter = GEOMETRY_BEGIN;
}

GrEn::exception Geometry::iterate(GrEn::Triangle& prim)
{
	for (; this->iter < this->bound; this->iter++)
	{
		if (isNotNull(this->primitives[this->iter]))
		{
			prim = primitives[this->iter];
			return 0;
		}
	}
	return GEOMETRY_END;
}
