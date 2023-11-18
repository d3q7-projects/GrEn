#pragma once
#include "GrEnDefinitions.h"


template<typename T>
void vecAdd(const GrEn::mat3<T>& mat1, const GrEn::mat3<T>& mat2, GrEn::mat3<T>& mat3)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat3[i][j] = mat2[i][j] + mat1[i][j];
		}
	}
}
template<typename T>
void vecAdd(const GrEn::mat4<T>& mat1, const GrEn::mat4<T>& mat2, GrEn::mat4<T>& mat3)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat3[i][j] = mat2[i][j] + mat1[i][j];
		}
	}
}