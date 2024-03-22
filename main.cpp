#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "window.h"
#include "input.h"
#include "graphics.h"
#include "matrix.h"
#include "mesh.h"
#include "camera.h"
#include "input.h"

//#pragma comment(linker, "/out:renderer.exe")

using namespace input;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND windowHandle = initWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600);

    if(windowHandle == nullptr)
        return 1;

    if(!initGraphics(windowHandle,800,600))
        return 2;

    mesh myMesh;

    bool success = loadMesh(myMesh, lpCmdLine);

    if(!success)
        return 3;

    mat4 world, camera, projection, viewport;
    world = matTransforms::translate(0,0,10) * matTransforms::rotateX(0) * matTransforms::scale(2,2,2);
    projection = matTransforms::perspective(90,800,600,1,100);
    viewport = matTransforms::viewPort(800,600);

    Camera cam;
    cam.setZ(-10);

    Gdiplus::Color clearColor(255,0,0,0);

    float x=0,y=0,z=0;
    float fowSpeed = 1;

    while(processMessage())
    {
        if (keyboard::keystates[VK_ESCAPE]) {
            break;
        }

        if(keyboard::keystates[0x57]) // 'W' key
        {
            float rad = (3.14159f * cam.getYaw()) / 180;

            x += sin(rad) * fowSpeed;
            z += cos(rad) * fowSpeed;
        }
        else if(keyboard::keystates[0x53]) // 'S' key
        {
            float rad = (3.14159f * cam.getYaw()) / 180;

            x -= sin(rad) * fowSpeed;
            z -= cos(rad) * fowSpeed;
        }
        if(keyboard::keystates[0x41]) // 'A' key
        {
            float rad = (3.14159f * (cam.getYaw()-90)) / 180;

            x += sin(rad) * fowSpeed;
            z += cos(rad) * fowSpeed;
        }
        else if(keyboard::keystates[0x44]) // 'D' key
        {
            float rad = (3.14159f * (cam.getYaw()+90)) / 180;

            x += sin(rad) * fowSpeed;
            z += cos(rad) * fowSpeed;
        }
        if(keyboard::keystates[VK_SPACE])
            y++;
        else if(keyboard::keystates[VK_SHIFT])
            y--;

        cam.setX(x);
        cam.setY(y);
        cam.setZ(z);
        cam.setPitch(cam.getPitch() + mouse::relativeY*0.5f);
        cam.setYaw(cam.getYaw() + mouse::relativeX*0.5f);

        mouse::relativeX = 0;
        mouse::relativeY = 0;

        camera = cam.makeCameraMatrix();

        clr(clearColor);
        drawMesh(myMesh,world,camera,projection,viewport);
        swapBuffers();
    }

    stopGraphics();

    DestroyWindow(windowHandle);

    return 0;
}


