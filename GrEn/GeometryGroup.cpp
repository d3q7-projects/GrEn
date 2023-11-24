#include "GeometryGroup.h"
#define GREN_OOB 3

GeometryGroup::GeometryGroup() : geometries(new const Geometry*[GEOMETRY_MAX]), bound(0), iter(0), available(0){}

GeometryGroup::GeometryGroup(const Geometry** prims, const int len) : geometries(new const Geometry* [GEOMETRY_MAX]), bound(len), iter(0), available(0) {
	for (size_t i = 0; i < len; i++)
	{
		if (i >= GEOMETRY_MAX)
		{
			return;
		}
		if (prims[i])
		{
			this->geometries[i] = prims[i];
		}
		else
		{
			this->bound--;
		}
	}
}

GeometryGroup::~GeometryGroup()
{
	delete[] this->geometries;
}

GrEn::exception GeometryGroup::addGeometry(const Geometry* geometry)
{
	if (this->bound == MAX_PRIMS) {
		return GrEn::exception(GREN_OOB);
	}
	this->geometries[this->available] = geometry;
	for (int i = this->available; i < this->bound; i++)
	{
		if (!this->geometries[i])
		{
			this->available = i;
			return 0;
		}
	}
	this->available = this->available == this->bound ? ++this->bound : this->bound;
	return 0;
}

int GeometryGroup::getLen() const
{
	int len = this->available;
	for (size_t i = this->available; i < this->bound; i++)
	{
		if (this->geometries[i])
		{
			len++;
		}
	}
	return len;
}

GrEn::exception GeometryGroup::removeGeometry(const int index)
{
	if (this->bound < MAX_PRIMS)
	{
		this->geometries[index] = nullptr;

		this->available = index < this->available ? index : this->available;
		this->bound = this->bound - 1 == index ? index : this->bound;
		return 0;
	}
	return GrEn::exception(GREN_OOB);
}

void GeometryGroup::resetIteration()
{
	this->iter = GEOMETRY_BEGIN;
}

GrEn::exception GeometryGroup::iterate(const Geometry*& geometry)
{
	for (; this->iter < this->bound; this->iter++)
	{
		if (this->geometries[this->iter])
		{
			geometry = this->geometries[this->iter];
			return 0;
		}
	}
	return GEOMETRY_END;
}
