#pragma once

namespace GrEn
{
	typedef struct rgba
	{
		float r;
		float g;
		float b;
		float a;
	} rgba;
	
	typedef unsigned int hexColor;
	hexColor rgbaToHex(rgba color);

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

	template<typename T>
	void mat3Add(mat3<T> a, mat3<T> b, mat3<T>& c);
	
	typedef struct Triangle
	{
		vec3<float> vertex[3];
		vec3<float> normal[3];
		vec2<float> uv[3];
	};
	template<typename T>
	void mat3Add(mat3<T> a, mat3<T> b, mat3<T>& c)
	{
		c[0][0] = a[0][0] + b[0][0];
		c[0][1] = a[0][1] + b[0][1];
		c[0][2] = a[0][2] + b[0][2];
		c[1][0] = a[1][0] + b[1][0];
		c[1][1] = a[1][1] + b[1][1];
		c[1][2] = a[1][2] + b[1][2];
		c[2][0] = a[2][0] + b[2][0];
		c[2][1] = a[2][1] + b[2][1];
		c[2][2] = a[2][2] + b[2][2];
	}
}