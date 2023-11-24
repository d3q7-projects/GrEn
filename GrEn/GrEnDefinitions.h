#pragma once
#include "GrEnColors.h"

namespace GrEn
{

	typedef struct material {
		rgba diffuse;
		rgba specular;
		float specularPower;
		float shininess;
	} material;

	template<typename T>
	struct vec2 {
		T x;
		T y;
	};
	
	template<typename T>
	struct vec3 {
		T x;
		T y;
		T z;
	};

	template<typename T>
	struct vec4 {
		T x;
		T y;
		T z;
		T w;
	};

	template<typename T>
	using mat3 = T[3][3];
	template<typename T>
	using mat4 = T[4][4];
	
	typedef struct Triangle
	{
		vec3<float> vertex[3];
		vec3<float> normal[3];
		vec2<float> uv[3];
	} Triangle;
}