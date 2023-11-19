#pragma once
#include "GrEnDefinitions.h"
#include <iostream>


template<typename T>
void matAdd(const GrEn::mat3<T>& mat1, const GrEn::mat3<T>& mat2, GrEn::mat3<T>& mat3)
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
void matAdd(const GrEn::mat4<T>& mat1, const GrEn::mat4<T>& mat2, GrEn::mat4<T>& mat3)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat3[i][j] = mat2[i][j] + mat1[i][j];
		}
	}
}

template<typename T>
void matAddEq(GrEn::mat3<T>& mat1, const GrEn::mat3<T>& mat2)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat1[i][j] += mat2[i][j];
		}
	}
}
template<typename T>
void matAddEq(GrEn::mat4<T>& mat1, const GrEn::mat4<T>& mat2)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat1[i][j] += mat2[i][j];
		}
	}
}


template<typename T>
void matSub(const GrEn::mat3<T>& mat1, const GrEn::mat3<T>& mat2, GrEn::mat3<T>& mat3)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat3[i][j] = mat2[i][j] - mat1[i][j];
		}
	}
}
template<typename T>
void matSub(const GrEn::mat4<T>& mat1, const GrEn::mat4<T>& mat2, GrEn::mat4<T>& mat3)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat3[i][j] = mat2[i][j] - mat1[i][j];
		}
	}
}

template<typename T>
void matSubEq(GrEn::mat3<T>& mat1, const GrEn::mat3<T>& mat2)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat1[i][j] -= mat2[i][j];
		}
	}
}
template<typename T>
void matSubEq(GrEn::mat4<T>& mat1, const GrEn::mat4<T>& mat2)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat1[i][j] -= mat2[i][j];
		}
	}
}


template<typename T>
void matScalarMult(const GrEn::mat3<T>& mat1, const T& s, GrEn::mat3<T>& mat2)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat2[i][j] = s * mat1[i][j];
		}
	}
}
template<typename T>
void matScalarMult(const GrEn::mat4<T>& mat1, const T& s, GrEn::mat4<T>& mat2)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat2[i][j] = s * mat1[i][j];
		}
	}
}

template<typename T>
void matScalarMultEq(GrEn::mat3<T>& mat1, const T& s)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat1[i][j] *= s;
		}
	}
}
template<typename T>
void matScalarMultEq(GrEn::mat4<T>& mat1, const T& s)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat1[i][j] *= s;
		}
	}
}


template<typename T>
void matScalarDiv(const GrEn::mat3<T>& mat1, const T& s, GrEn::mat3<T>& mat2)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat2[i][j] = mat1[i][j] / s;
		}
	}
}
template<typename T>
void matScalarDiv(const GrEn::mat4<T>& mat1, const T& s, GrEn::mat4<T>& mat2)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat2[i][j] = mat1[i][j] / s;
		}
	}
}

template<typename T>
void matScalarDivEq(GrEn::mat3<T>& mat1, const T& s)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			mat1[i][j] /= s;
		}
	}
}
template<typename T>
void matScalarDivEq(GrEn::mat4<T>& mat1, const T& s)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat1[i][j] /= s;
		}
	}
}


template<typename T>
void matMult(const GrEn::mat3<T>& mat1, const GrEn::mat3<T>& mat2, GrEn::mat3<T>& mat3)
{
	mat3[0][0] = mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0] + mat1[0][2] * mat2[2][0];
	mat3[0][1] = mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1] + mat1[0][2] * mat2[2][1];
	mat3[0][2] = mat1[0][0] * mat2[0][2] + mat1[0][1] * mat2[1][2] + mat1[0][2] * mat2[2][2];

	mat3[1][0] = mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0] + mat1[1][2] * mat2[2][0];
	mat3[1][1] = mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1] + mat1[1][2] * mat2[2][1];
	mat3[1][2] = mat1[1][0] * mat2[0][2] + mat1[1][1] * mat2[1][2] + mat1[1][2] * mat2[2][2];

	mat3[2][0] = mat1[2][0] * mat2[0][0] + mat1[2][1] * mat2[1][0] + mat1[2][2] * mat2[2][0];
	mat3[2][1] = mat1[2][0] * mat2[0][1] + mat1[2][1] * mat2[1][1] + mat1[2][2] * mat2[2][1];
	mat3[2][2] = mat1[2][0] * mat2[0][2] + mat1[2][1] * mat2[1][2] + mat1[2][2] * mat2[2][2];
}
template<typename T>
void matMult(const GrEn::mat4<T>& mat1, const GrEn::mat4<T>& mat2, GrEn::mat4<T>& mat3)
{
	mat3[0][0] = mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0] + mat1[0][2] * mat2[2][0] + mat1[0][3] * mat2[3][0];
	mat3[0][1] = mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1] + mat1[0][2] * mat2[2][1] + mat1[0][3] * mat2[3][1];
	mat3[0][2] = mat1[0][0] * mat2[0][2] + mat1[0][1] * mat2[1][2] + mat1[0][2] * mat2[2][2] + mat1[0][3] * mat2[3][2];

	mat3[1][0] = mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0] + mat1[1][2] * mat2[2][0] + mat1[1][3] * mat2[3][0];
	mat3[1][1] = mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1] + mat1[1][2] * mat2[2][1] + mat1[1][3] * mat2[3][1];
	mat3[1][2] = mat1[1][0] * mat2[0][2] + mat1[1][1] * mat2[1][2] + mat1[1][2] * mat2[2][2] + mat1[1][3] * mat2[3][2];

	mat3[2][0] = mat1[2][0] * mat2[0][0] + mat1[2][1] * mat2[1][0] + mat1[2][2] * mat2[2][0] + mat1[2][3] * mat2[3][0];
	mat3[2][1] = mat1[2][0] * mat2[0][1] + mat1[2][1] * mat2[1][1] + mat1[2][2] * mat2[2][1] + mat1[2][3] * mat2[3][1];
	mat3[2][2] = mat1[2][0] * mat2[0][2] + mat1[2][1] * mat2[1][2] + mat1[2][2] * mat2[2][2] + mat1[2][3] * mat2[3][2];

	mat3[3][0] = mat1[3][0] * mat2[0][0] + mat1[3][1] * mat2[1][0] + mat1[3][2] * mat2[2][0] + mat1[3][3] * mat2[3][0];
	mat3[3][1] = mat1[3][0] * mat2[0][1] + mat1[3][1] * mat2[1][1] + mat1[3][2] * mat2[2][1] + mat1[3][3] * mat2[3][1];
	mat3[3][2] = mat1[3][0] * mat2[0][2] + mat1[3][1] * mat2[1][2] + mat1[3][2] * mat2[2][2] + mat1[3][3] * mat2[3][2];
}


template<typename T>
void matVecMult(const GrEn::mat3<T>& mat, const GrEn::vec3<T>& vec1, GrEn::vec3<T>& vec2)
{
	vec2.x = mat[0][0] * vec1.x + mat[0][1] * vec1.y + mat[0][2] * vec1.z;
	vec2.y = mat[1][0] * vec1.x + mat[1][1] * vec1.y + mat[1][2] * vec1.z;
	vec2.z = mat[2][0] * vec1.x + mat[2][1] * vec1.y + mat[2][2] * vec1.z;
}
template<typename T>
void matVecMult(const GrEn::mat4<T>& mat, const GrEn::vec4<T>& vec1, GrEn::vec4<T>& vec2)
{
	vec2.x = mat[0][0] * vec1.x + mat[0][1] * vec1.y + mat[0][2] * vec1.z + mat[0][2] * vec1.w;
	vec2.y = mat[1][0] * vec1.x + mat[1][1] * vec1.y + mat[1][2] * vec1.z + mat[1][2] * vec1.w;
	vec2.z = mat[2][0] * vec1.x + mat[2][1] * vec1.y + mat[2][2] * vec1.z + mat[2][2] * vec1.w;
	vec2.w = mat[3][0] * vec1.x + mat[3][1] * vec1.y + mat[3][2] * vec1.z + mat[3][2] * vec1.w;
}

template<typename T>
T matDeterminent(const GrEn::mat3<T>& mat)
{
	return mat[0][0] * mat[1][1] * mat[2][2] +
			mat[0][1] * mat[1][2] * mat[2][0] +
			mat[0][2] * mat[1][0] * mat[2][1] -
			mat[0][2] * mat[1][1] * mat[2][0] -
			mat[0][1] * mat[1][0] * mat[2][2] -
			mat[0][0] * mat[1][2] * mat[2][1];
}

template<typename T>
void matTranspose(GrEn::mat3<T>& mat)
{
	T temp = mat[1][0];
	mat[1][0] = mat[0][1];
	mat[0][1] = temp;

	temp = mat[2][0];
	mat[2][0] = mat[0][2];
	mat[0][2] = temp;

	temp = mat[1][2];
	mat[1][2] = mat[2][1];
	mat[2][1] = temp;
}
template<typename T>
void matGetTranspose(const GrEn::mat3<T>& mat1, GrEn::mat3<T>& mat2)
{
	mat2[0][0] = mat1[0][0];
	mat2[1][1] = mat1[1][1];
	mat2[2][2] = mat1[2][2];
	mat2[0][1] = mat1[1][0];
	mat2[0][2] = mat1[2][0];
	mat2[1][0] = mat1[0][1];
	mat2[1][2] = mat1[2][1];
	mat2[2][0] = mat1[0][2];
	mat2[2][1] = mat1[1][2];
}

template<typename T>
void matGetAdjunt(const GrEn::mat3<T>& mat1, GrEn::mat3<T>& mat2)
{
	mat2[0][0] = mat1[1][1] * mat1[2][2] - mat1[1][2] * mat1[2][1];
	mat2[0][1] = mat1[2][1] * mat1[0][2] - mat1[0][1] * mat1[2][2];
	mat2[0][2] = mat1[0][1] * mat1[1][2] - mat1[1][1] * mat1[0][2];

	mat2[1][0] = mat1[2][0] * mat1[1][2] - mat1[1][0] * mat1[2][2];
	mat2[1][1] = mat1[0][0] * mat1[2][2] - mat1[2][0] * mat1[0][2];
	mat2[1][2] = mat1[1][0] * mat1[0][2] - mat1[0][0] * mat1[1][2];

	mat2[2][0] = mat1[1][0] * mat1[2][1] - mat1[2][0] * mat1[1][1];
	mat2[2][1] = mat1[2][0] * mat1[0][1] - mat1[0][0] * mat1[2][1];
	mat2[2][2] = mat1[0][0] * mat1[1][1] - mat1[1][0] * mat1[0][1];
}

template<typename T>
void matGetInverse(const GrEn::mat3<T>& mat1, GrEn::mat3<T>& mat2)
{
	//fix
	matGetAdjunt(mat1, mat2);
	matScalarDivEq(mat2, matDeterminent(mat1));
}



template<typename T>
void matPrint(const GrEn::mat3<T>& mat1) {
	std::cout << "[\t" << mat1[0][0] << ",\t" << mat1[0][1] << ",\t" << mat1[0][2] << "\t]" << std::endl;
	std::cout << "[\t" << mat1[1][0] << ",\t" << mat1[1][1] << ",\t" << mat1[1][2] << "\t]" << std::endl;
	std::cout << "[\t" << mat1[2][0] << ",\t" << mat1[2][1] << ",\t" << mat1[2][2] << "\t]" << std::endl;
}
template<typename T>
void matPrint(const GrEn::mat4<T>& mat1) {
	std::cout << "[\t" << mat1[0][0] << ",\t" << mat1[0][1] << ",\t" << mat1[0][2] << ",\t" << mat1[0][3] << "\t]" << std::endl;
	std::cout << "[\t" << mat1[1][0] << ",\t" << mat1[1][1] << ",\t" << mat1[1][2] << ",\t" << mat1[1][3] << "\t]" << std::endl;
	std::cout << "[\t" << mat1[2][0] << ",\t" << mat1[2][1] << ",\t" << mat1[2][2] << ",\t" << mat1[2][3] << "\t]" << std::endl;
	std::cout << "[\t" << mat1[3][0] << ",\t" << mat1[3][1] << ",\t" << mat1[3][2] << ",\t" << mat1[3][3] << "\t]" << std::endl;
}