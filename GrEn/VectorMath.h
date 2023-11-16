#pragma once
#include "GrEnDefinitions.h"

template<typename T>
void vecAdd(const GrEn::vec2<T>& v1, const GrEn::vec2<T>& v2, GrEn::vec2<T>& v3)
{
	v3.x = v2.x + v1.x;
	v3.y = v2.y + v1.y;
}
template<typename T>
void vecAdd(const GrEn::vec3<T>& v1, const GrEn::vec3<T>& v2, GrEn::vec3<T>& v3)
{
	v3.x = v2.x + v1.x;
	v3.y = v2.y + v1.y;
	v3.z = v2.z + v1.z;
}
template<typename T>
void vecAdd(const GrEn::vec4<T>& v1, const GrEn::vec4<T>& v2, GrEn::vec4<T>& v3)
{
	v3.x = v2.x + v1.x;
	v3.y = v2.y + v1.y;
	v3.z = v2.z + v1.z;
	v3.w = v2.w + v1.w;
}


template<typename T>
void vecAddEq(GrEn::vec2<T>& v1, const GrEn::vec2<T>& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
}
template<typename T>
void vecAddEq(GrEn::vec3<T>& v1, const GrEn::vec3<T>& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
}
template<typename T>
void vecAddEq(GrEn::vec4<T>& v1, const GrEn::vec4<T>& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
}


template<typename T>
void vecSub(const GrEn::vec2<T>& v1, const GrEn::vec2<T>& v2, GrEn::vec2<T>& v3)
{
	v3.x = v2.x - v1.x;
	v3.y = v2.y - v1.y;
}
template<typename T>
void vecSub(const GrEn::vec3<T>& v1, const GrEn::vec3<T>& v2, GrEn::vec3<T>& v3)
{
	v3.x = v2.x - v1.x;
	v3.y = v2.y - v1.y;
	v3.z = v2.z - v1.z;
}
template<typename T>
void vecSub(const GrEn::vec4<T>& v1, const GrEn::vec4<T>& v2, GrEn::vec4<T>& v3)
{
	v3.x = v2.x - v1.x;
	v3.y = v2.y - v1.y;
	v3.z = v2.z - v1.z;
	v3.w = v2.w - v1.w;
}


template<typename T>
void vecSubEq(GrEn::vec2<T>& v1, const GrEn::vec2<T>& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
}
template<typename T>
void vecSubEq(GrEn::vec3<T>& v1, const GrEn::vec3<T>& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
}
template<typename T>
void vecSubEq(GrEn::vec4<T>& v1, const GrEn::vec4<T>& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
}


template<typename T>
void vecScalarProd(const GrEn::vec2<T>& v1, const T& s, GrEn::vec2<T>& v3)
{
	v3.x = s * v1.x;
	v3.y = s * v1.y;
}
template<typename T>
void vecScalarProd(const GrEn::vec3<T>& v1, const T& s, GrEn::vec3<T>& v3)
{
	v3.x = s * v1.x;
	v3.y = s * v1.y;
	v3.z = s * v1.z;
}
template<typename T>
void vecScalarProd(const GrEn::vec4<T>& v1, const T& s, GrEn::vec4<T>& v3)
{
	v3.x = s * v1.x;
	v3.y = s * v1.y;
	v3.z = s * v1.z;
	v3.w = s * v1.w;
}

template<typename T>
void vecScalarProdEq(GrEn::vec2<T>& v1, const T& s)
{
	v1.x *= s;
	v1.y *= s;
}
template<typename T>
void vecScalarProdEq(GrEn::vec3<T>& v1, const T& s)
{
	v1.x *= s;
	v1.y *= s;
	v1.z *= s;
}
template<typename T>
void vecScalarProdEq(GrEn::vec4<T>& v1, const T& s)
{
	v1.x *= s;
	v1.y *= s;
	v1.z *= s;
	v1.w *= s;
}

template<typename T>
void vecScalarDiv(const GrEn::vec2<T>& v1, const T& s, GrEn::vec2<T>& v3)
{
	v3.x = v1.x / s;
	v3.y = v1.y / s;
}
template<typename T>
void vecScalarDiv(const GrEn::vec3<T>& v1, const T& s, GrEn::vec3<T>& v3)
{
	v3.x = v1.x / s;
	v3.y = v1.y / s;
	v3.z = v1.z / s;
}
template<typename T>
void vecScalarDiv(const GrEn::vec4<T>& v1, const T& s, GrEn::vec4<T>& v3)
{
	v3.x = v1.x / s;
	v3.y = v1.y / s;
	v3.z = v1.z / s;
	v3.w = v1.w / s;
}

template<typename T>
void vecScalarDivEq(GrEn::vec2<T>& v1, const T& s)
{
	v1.x /= s;
	v1.y /= s;
}
template<typename T>
void vecScalarDivEq(GrEn::vec3<T>& v1, const T& s)
{
	v1.x /= s;
	v1.y /= s;
	v1.z /= s;
}
template<typename T>
void vecScalarDivEq(GrEn::vec4<T>& v1, const T& s)
{
	v1.x /= s;
	v1.y /= s;
	v1.z /= s;
	v1.w /= s;
}


template<typename T>
T vecDotProd(const GrEn::vec2<T>& v1, const GrEn::vec2<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
template<typename T>
T vecDotProd(const GrEn::vec3<T>& v1, const GrEn::vec3<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template<typename T>
T vecDotProd(const GrEn::vec4<T>& v1, const GrEn::vec4<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}


template<typename T>
void vecCrossProd(const GrEn::vec3<T>& v1, const GrEn::vec3<T>& v2, GrEn::vec3<T>& v3)
{
	v3.x = v1.y* v2.z - v1.z * v2.y;
	v3.y = v1.z* v2.x - v1.x * v2.z;
	v3.z = v1.x* v2.y - v1.y * v2.x;
}

