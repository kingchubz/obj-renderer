#pragma once

#include "window.h"
#include "vector.h"

#include "matrix.h"
#include "mesh.h"

bool initGraphics(HWND handle, int w, int h);
void stopGraphics();

void clr(Gdiplus::Color color);
void swapBuffers();

void putPixel(int x, int y, float z, Gdiplus::Color &color);
void fillTriangle(vec4 p1, vec4 p2, vec4 p3, Gdiplus::Color &color);
void drawMesh(mesh &originalMesh, mat4 &world, mat4 &camera, mat4 &projection, mat4 &viewport);
