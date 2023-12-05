#include "MatrixMath.hpp"

void matGetRotationX(GrEn::mat3<float>& mat, const float angle)
{
	mat[0][0] = 1;	mat[0][1] = 0;				mat[0][2] = 0;
	mat[1][0] = 0; 	mat[1][1] = cosf(angle);	mat[1][2] = -sinf(angle);
	mat[2][0] = 0; 	mat[2][1] = sinf(angle);	mat[2][2] = cosf(angle);
}

void matGetRotationY(GrEn::mat3<float>& mat, const float angle)
{
	mat[0][0] = cosf(angle);	mat[0][1] = 0;	mat[0][2] = sinf(angle);
	mat[1][0] = 0; 				mat[1][1] = 1;	mat[1][2] = 0;
	mat[2][0] = -sinf(angle);	mat[2][1] = 0;	mat[2][2] = cosf(angle);
}

void matGetRotationZ(GrEn::mat3<float>& mat, const float angle)
{
	mat[0][0] = cosf(angle); mat[0][1] = -sinf(angle);	mat[0][2] = 0;
	mat[1][0] = sinf(angle); mat[1][1] = cosf(angle);	mat[1][2] = 0;
	mat[2][0] = 0; 			 mat[2][1] = 0;				mat[2][2] = 1;
}

void matGetRotationAxis(GrEn::mat3<float>& mat, const GrEn::vec3<float>& axis, const float angle)
{
	const float cosA = cosf(angle);
	const float sinA = sinf(angle);
	const float adjCos = (1.0f - cosA);

	mat[0][0] = cosA + axis.x * axis.x * adjCos;			mat[0][1] = axis.x * axis.y * adjCos - axis.z * sinA;	mat[0][2] = axis.x * axis.z * adjCos + axis.y * sinA;
	mat[1][0] = axis.y * axis.x * adjCos + axis.z * sinA; 	mat[1][1] = cosA + axis.y * axis.y * adjCos;			mat[1][2] = axis.y * axis.z * adjCos - axis.x * sinA;
	mat[2][0] = axis.z * axis.x * adjCos - axis.y * sinA; 	mat[2][1] = axis.z * axis.y * adjCos + axis.x * sinA;	mat[2][2] = axis.z * axis.z * adjCos;
}

void matGetRotationXYZ(GrEn::mat4<float>& mat, const float aX, const float aY, const float aZ)
{
	const float cosAlpha = cosf(aX);
	const float cosBeta = cosf(aY);
	const float cosGamma = cosf(aZ);
	const float sinAlpha = sinf(aX);
	const float sinBeta = sinf(aY);
	const float sinGamma = sinf(aZ);

	mat[0][0] = cosBeta * cosGamma;	mat[0][1] = sinAlpha * sinBeta * cosGamma - cosAlpha * sinGamma;	mat[0][2] = cosAlpha * sinBeta * cosGamma + sinAlpha * sinGamma;	mat[0][3] = 0;
	mat[1][0] = cosBeta * sinGamma;	mat[1][1] = sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma;	mat[1][2] = cosAlpha * sinBeta * sinGamma - sinAlpha * cosGamma;	mat[1][3] = 0;
	mat[2][0] = -sinBeta;			mat[2][1] = sinAlpha * cosBeta;										mat[2][2] = cosAlpha * cosBeta;										mat[2][3] = 0;
	mat[3][0] = 0;					mat[3][1] = 0;														mat[3][2] = 0;														mat[3][3] = 1;
}


