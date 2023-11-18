#include "VectorMath.hpp"
#include <immintrin.h>

void vecNormalize(GrEn::vec3<float>& v1)
{
    const float vLen = vecLen(v1);
    float vecArr[8] = { v1.x, v1.y, v1.z,0,0,0,0,0 };
    const float lenArr[8] = { vLen, vLen, vLen,0,0,0,0,0 };
    __m256 _srcVecReisger = _mm256_loadu_ps(vecArr);
    __m256 _srcLenReisger = _mm256_loadu_ps(lenArr);
    __m256 _dstRegister = _mm256_div_ps(_srcVecReisger, _srcLenReisger);
    _mm256_storeu_ps(vecArr, _dstRegister);
    v1.x = vecArr[0]; v1.y = vecArr[1]; v1.z = vecArr[2];
}

float vecMag(GrEn::vec3<float>& v1)
{
    return vecDotProd(v1, v1);
}

float vecLen(GrEn::vec3<float>& v1)
{
    float array[4];

    __m128 _srcReisger = _mm_set1_ps(vecDotProd(v1, v1));
    __m128 _dstRegister = _mm_sqrt_ps(_srcReisger);
    _mm_storeu_ps(array, _dstRegister);
    return array[0];
}
