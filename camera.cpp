#include "camera.h"
//
//GETTERS
////
float Camera::getX()
{
    return camX;
}

float Camera::getY()
{
    return camY;
}

float Camera::getZ()
{
    return camZ;
}

float Camera::getPitch()
{
    return pitch;
}
float Camera::getYaw()
{
    return yaw;
}

float Camera::getRoll()
{
    return roll;
}

//
//SETTERS
//

void Camera::setX(float x)
{
    camX = x;
}

void Camera::setY(float y)
{
    camY = y;
}

void Camera::setZ(float z)
{
    camZ = z;
}

void Camera::setPitch(float pitch)
{
    if(pitch > 90)
        pitch = 90;
    else if(pitch < -90)
        pitch = -90;

    this->pitch = pitch;
}

void Camera::setYaw(float yaw)
{
    if(yaw > 180)
        yaw = -180;
    else if(yaw < -180)
        yaw = 180;

    this->yaw = yaw;
}

void Camera::setRoll(float roll)
{
    if(roll > 180)
        roll = -180;
    else if(roll < -180)
        roll = 180;

    this->roll = roll;
}
//
//MATRIX
//
mat4 Camera::makeCameraMatrix()
{
    return matTransforms::rotateX(-pitch) * matTransforms::rotateY(-yaw) * matTransforms::rotateZ(-roll) * matTransforms::translate(-camX,-camY,-camZ);
}
