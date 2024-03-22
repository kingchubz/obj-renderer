#include "vector.h"

                        /////////////
                        //Vector 2d//
                        /////////////
vec2::vec2()
{
    x = y = 0;
}

vec2::vec2(float x,float y)
: x(x),
  y(y)
{
}

vec2::vec2(const vec2& v1)
{
    x = v1.x;
    y = v1.y;
}

vec2 vec2::operator +(vec2 v1)
{
    vec2 v2;

    v2.x = x + v1.x;
    v2.y = y + v1.y;

    return v2;
}

vec2 vec2::operator -(vec2 v1)
{
    vec2 v2;

    v2.x = x - v1.x;
    v2.y = y - v1.y;

    return v2;
}

float vec2::operator *(vec2 v1)
{
    float sum;

    sum = x*v1.x + y*v1.y;

    return sum;
}

vec2 vec2::operator /(float f)
{
    vec2 v1;

    v1.x = x / f;
    v1.y = y / f;

    return v1;
}

std::string vec2::str()
{
    std::stringstream out;
    out << x << " " << y;
    return out.str();
}

                        /////////////
                        //Vector 3d//
                        /////////////
vec3::vec3()
{
    x = y = z = 0;
}

vec3::vec3(float x,float y,float z)
: x(x),
  y(y),
  z(z)
{
}

vec3::vec3(const vec3& v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;
}

vec3::vec3(vec4& v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;
}

vec3 vec3::operator +(vec3 v1)
{
    vec3 v2;

    v2.x = x + v1.x;
    v2.y = y + v1.y;
    v2.z = z + v1.z;

    return v2;
}

vec3 vec3::operator -(vec3 v1)
{
    vec3 v2;

    v2.x = x - v1.x;
    v2.y = y - v1.y;
    v2.z = z - v1.z;

    return v2;
}

float vec3::operator *(vec3 v1)
{
    float sum;

    sum = x*v1.x + y*v1.y + z*v1.z;

    return sum;
}

vec3 vec3::operator /(float f)
{
    vec3 v1;

    v1.x = x / f;
    v1.y = y / f;
    v1.z = z / f;

    return v1;
}

vec3 vec3::operator=(vec4 v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;

    return {x,y,z};
}

std::string vec3::str()
{
    std::stringstream out;
    out << x << " " << y << " " << z;
    return out.str();
}

                        /////////////
                        //Vector 4d//
                        /////////////

vec4::vec4()
{
    x = y = z = 0;
    w = 1;
}

vec4::vec4(float x,float y,float z, float w)
: x(x),
  y(y),
  z(z),
  w(w)
{
}

vec4::vec4(const vec3& v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;
    w = 1;
}

vec4::vec4(const vec4& v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;
    w = v1.w;
}

vec4 vec4::operator +(vec4 v1)
{
    vec4 v2;

    v2.x = x + v1.x;
    v2.y = y + v1.y;
    v2.z = z + v1.z;
    v2.w = w + v1.w;

    return v2;
}

vec4 vec4::operator -(vec4 v1)
{
    vec4 v2;

    v2.x = x - v1.x;
    v2.y = y - v1.y;
    v2.z = z - v1.z;
    v2.w = w - v1.w;

    return v2;
}

float vec4::operator *(vec4 v1)
{
    float sum;

    sum = x*v1.x + y*v1.y + z*v1.z + w*v1.w;

    return sum;
}

vec4 vec4::operator /(float f)
{
    vec4 v1;

    v1.x = x / f;
    v1.y = y / f;
    v1.z = z / f;
    v1.w = w / f;

    return v1;
}

std::string vec4::str()
{
    std::stringstream out;
    out << x << " " << y << " " << z << " " << w;
    return out.str();
}
