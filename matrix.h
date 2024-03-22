#pragma once

#include <math.h>

#include "vector.h"

class mat3
{
    public:
        mat3();

        vec3 & operator [](int i);
        mat3 operator +(mat3 m1);
        mat3 operator *(mat3 m1);
        vec3 operator *(vec3 v1);

        std::string str();

    private:
        vec3 rows[3];
};

class mat4
{
    public:
        mat4();

        vec4 & operator [](int i);
        mat4 operator +(mat4 m1);
        mat4 operator *(mat4 m1);
        vec4 operator *(vec4 v1);

        std::string str();

    private:
        vec4 rows[4];
};

namespace matTransforms
{
    mat4 translate(float x, float y, float z);
    mat4 scale(float x, float y, float z);
    mat4 rotateX(float deg);
    mat4 rotateY(float deg);
    mat4 rotateZ(float deg);
    mat4 perspective(float fov, float width, float height, float near, float far);
    mat4 viewPort(float width, float height);
    //... add euler, ?camera?
};
