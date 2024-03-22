#include "matrix.h"

                        //////////////
                        //Matrix 3x3//
                        //////////////

mat3::mat3()
{
    rows[0].x = 1;
    rows[1].y = 1;
    rows[2].z = 1;
}

vec3 & mat3::operator [](int i)
{
    return rows[i];
}

mat3 mat3::operator +(mat3 m1)
{
    mat3 m2;

    m2[0] = rows[0] + m1[0];
    m2[1] = rows[1] + m1[1];
    m2[2] = rows[2] + m1[2];

    return m2;
}

mat3 mat3::operator *(mat3 m1)
{
    mat3 m2;

    for(int i = 0; i < 3; i++)
    {
        m2[i].x = rows[i] * vec3(m1[0].x,m1[1].x,m1[2].x);
        m2[i].y = rows[i] * vec3(m1[0].y,m1[1].y,m1[2].y);
        m2[i].z = rows[i] * vec3(m1[0].z,m1[1].z,m1[2].z);
    }

    return m2;
}

vec3 mat3::operator *(vec3 v1)
{
    vec3 v2;

    v2.x = rows[0] * v1;
    v2.y = rows[1] * v1;
    v2.z = rows[2] * v1;

    return v2;
}

std::string mat3::str()
{
    std::stringstream out;
    out << rows[0].str() << "\n" << rows[1].str() << "\n" << rows[2].str();
    return out.str();
}

                        //////////////
                        //Matrix 4x4//
                        //////////////

mat4::mat4()
{
    rows[0] = {1,0,0,0};
    rows[1] = {0,1,0,0};
    rows[2] = {0,0,1,0};
    rows[3] = {0,0,0,1};
}

vec4 & mat4::operator [](int i)
{
    return rows[i];
}

mat4 mat4::operator +(mat4 m1)
{
    mat4 m2;

    m2[0] = rows[0] + m1[0];
    m2[1] = rows[1] + m1[1];
    m2[2] = rows[2] + m1[2];
    m2[3] = rows[3] + m1[3];

    return m2;
}

mat4 mat4::operator *(mat4 m1)
{
    mat4 m2;

    for(int i = 0; i < 4; i++)
    {
        m2[i].x = rows[i] * vec4(m1[0].x,m1[1].x,m1[2].x,m1[3].x);
        m2[i].y = rows[i] * vec4(m1[0].y,m1[1].y,m1[2].y,m1[3].y);
        m2[i].z = rows[i] * vec4(m1[0].z,m1[1].z,m1[2].z,m1[3].z);
        m2[i].w = rows[i] * vec4(m1[0].w,m1[1].w,m1[2].w,m1[3].w);
    }

    return m2;
}

vec4 mat4::operator *(vec4 v1)
{
    vec4 v2;

    v2.x = rows[0] * v1;
    v2.y = rows[1] * v1;
    v2.z = rows[2] * v1;
    v2.w = rows[3] * v1;

    return v2;
}

std::string mat4::str()
{
    std::stringstream out;
    out << rows[0].str() << "\n" << rows[1].str() << "\n" << rows[2].str() << "\n" << rows[3].str();
    return out.str();
}

                        /////////////////////
                        //Matrix Transforms//
                        /////////////////////

mat4 matTransforms::translate(float x, float y, float z)
{
    mat4 tranclateMat;

    tranclateMat[0].w = x;
    tranclateMat[1].w = y;
    tranclateMat[2].w = z;

    return tranclateMat;
}

mat4 matTransforms::scale(float x, float y, float z)
{
    mat4 scaleMat;

    scaleMat[0].x = x;
    scaleMat[1].y = y;
    scaleMat[2].z = z;

    return scaleMat;
}

mat4 matTransforms::rotateX(float deg)
{
    mat4 rotMat;

    float rad = (3.14159f * deg) / 180.0f;

    rotMat[1] = {0,cos(rad),-sin(rad),0};
    rotMat[2] = {0,sin(rad),cos(rad),0};

    return rotMat;
}

mat4 matTransforms::rotateY(float deg)
{
    mat4 rotMat;

    float rad = (3.14159f * deg) / 180.0f;

    rotMat[0] = {cos(rad),0,sin(rad),0};
    rotMat[2] = {-sin(rad),0,cos(rad),0};

    return rotMat;
}

mat4 matTransforms::rotateZ(float deg)
{
    mat4 rotMat;

    float rad = (3.14159f * deg) / 180.0f;

    rotMat[0] = {cos(rad),-sin(rad),0,0};
    rotMat[1] = {sin(rad),cos(rad),0,0};

    return rotMat;
}

mat4 matTransforms::perspective(float fov, float width, float height, float near, float far)
{
    mat4 projMat;

    float tanHalfFOV = 1.0f / tan(fov*0.5f/180.0f*3.14159f);

    projMat[0] = {tanHalfFOV,0,0,0};
    projMat[1] = {0,-tanHalfFOV,0,0};
    projMat[2] = {0,0,(far + near) / (far - near),(-2.0f * far * near) / (far - near)};
    projMat[3] = {0,0,1,0};

    return projMat;
}

mat4 matTransforms::viewPort(float width, float height)
{
    return matTransforms::scale(width*0.5f,height*0.5f,1) * matTransforms::translate(1,1,0);
}
