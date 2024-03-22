#pragma once

#include "matrix.h"

class Camera
{
    public:
        float getX();
        float getY();
        float getZ();
        float getPitch();
        float getYaw();
        float getRoll();

        void setX(float x);
        void setY(float y);
        void setZ(float z);
        void setPitch(float pitch);
        void setYaw(float yaw);
        void setRoll(float roll);

        mat4 makeCameraMatrix();

    private:
        float camX=0, camY=0, camZ=0;
        float pitch=0, yaw=0, roll=0;
};
