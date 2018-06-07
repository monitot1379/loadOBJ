#ifndef MATHFUNC_H
#define MATHFUNC_H
#include<cmath>
#include<assert.h>
#include<gl\glut.h>
static void vZero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}

static void vSet(float *v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

static void vSub(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] - src2[0];
    dst[1] = src1[1] - src2[1];
    dst[2] = src1[2] - src2[2];
}
static void vCopy(const float *v1, float *v2)
{
    register int i;
    for (i = 0; i < 3; i++)
        v2[i] = v1[i];
}
static void vCross(const float *v1, const float *v2, float *cross)
{
    float temp[3];

    temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    vCopy(temp, cross);
}

//空间点到原点的长度
static float vLength(const float *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

//将每个坐标乘以一个浮点数
static void vScale(float *v, float div)
{
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

//单位化
static void vNormal(float *v)
{
    vScale(v, 1.0f / vLength(v));
}
#endif // MATHFUNC_H
