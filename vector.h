#pragma once

#include <string>
#include <sstream>

class vec2;
class vec3;
class vec4;

class vec2
{
    public:
        vec2();
        vec2(float x,float y);
        vec2(const vec2& v1);

        vec2 operator +(vec2 v1);
        vec2 operator -(vec2 v1);
        float operator *(vec2 v1);
        vec2 operator /(float f);

        std::string str();

        float x, y;
};

class vec3
{
    public:
        vec3();
        vec3(float x,float y,float z);
        vec3(const vec3& v1);
        vec3(vec4& v1);

        vec3 operator +(vec3 v1);
        vec3 operator -(vec3 v1);
        float operator *(vec3 v1);
        vec3 operator /(float f);
        vec3 operator =(vec4 v1);

        std::string str();

        float x, y, z;
};

class vec4
{
    public:
        vec4();
        vec4(float x,float y,float z, float w);
        vec4(const vec3& v1);
        vec4(const vec4& v1);

        vec4 operator +(vec4 v1);
        vec4 operator -(vec4 v1);
        float operator *(vec4 v1);
        vec4 operator /(float f);

        std::string str();

        float x, y, z, w;
};
