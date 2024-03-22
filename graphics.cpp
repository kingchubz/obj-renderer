#include "graphics.h"

using namespace Gdiplus;

HWND hwnd;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

int width = 0, height = 0;
Rect *drawArea = nullptr;

Graphics *frontScreen = nullptr;            //screen

Bitmap *backScreen = nullptr;               //back buffer image
BitmapData *backScreenData = nullptr;       //
unsigned int *backScreenContents = nullptr; //raw back buffer image data

float *depthBuffer = nullptr;

bool initGraphics(HWND handle, int w, int h)
{
    hwnd = handle;
    width = w;
    height = h;

    Status status = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    if(status != Status::Ok)
        return false;

    frontScreen = new Graphics(hwnd);
    backScreen = new Bitmap(width, height);
    backScreenData = new BitmapData();
    depthBuffer = new float[width*height];

    drawArea = new Rect(0,0,width,height);

    backScreen->LockBits(drawArea, ImageLockModeWrite, PixelFormat32bppARGB, backScreenData);

    backScreenContents = (unsigned int *)(backScreenData->Scan0);

    return true;
}

void stopGraphics()
{
    GdiplusShutdown(gdiplusToken);
}

void clr(Color color)
{
    std::fill_n(backScreenContents, (height-1) * backScreenData->Stride / 4 + width - 1, color.GetValue());
    std::fill_n(depthBuffer, width*height, -1.0);
}

void swapBuffers()
{
    backScreen->UnlockBits(backScreenData);
    CachedBitmap cachedScreen(backScreen, frontScreen);

    frontScreen->DrawCachedBitmap(&cachedScreen,0,0);

    RedrawWindow(hwnd,NULL,NULL,RDW_INVALIDATE);

    backScreen->LockBits(drawArea, ImageLockModeWrite, PixelFormat32bppARGB, backScreenData);
    backScreenContents = (unsigned int *)backScreenData->Scan0;
}

void putPixel(int x, int y, float z, Color &color)
{
    if(x < 0 || x >= width)
        return;
    if(y < 0 || y >= height)
        return;
    if(z > depthBuffer[y * width  + x])
    {
        backScreenContents[y * backScreenData->Stride / 4 + x] = color.GetValue();
        depthBuffer[y * width  + x] = z;
    }
}

void drawHorizontalLine(vec4 p1, vec4 p2, Gdiplus::Color &color)
{

    int dx = p2.x - p1.x;

    if(dx < 0)
    {
        std::swap(p1,p2);
        dx = fabs(dx);
    }

    int y = p1.y;

    float z = p1.z;
    float zi = (p2.z - p1.z) / dx;

    int x2 = p2.x;
    for(int x1 = p1.x; x1 <= x2; x1++)
    {
        putPixel(x1,y,z,color);

        z+=zi;
    }
}

//helper function for fillTriangle
void fillFlatSideTriangle(vec4 base1, vec4 base2, vec4 top, Gdiplus::Color &color)
{
    int dy = top.y - base1.y;
    int steps = fabs(dy);
    dy = (dy > 0) - (dy < 0);

    float dx1 = (top.x - base1.x)/steps;
    float dz1 = (top.z - base1.z)/steps;

    float dx2 = (top.x - base2.x)/steps;
    float dz2 = (top.z - base2.z)/steps;

    vec4 p1, p2;

    p1.x = base1.x; p1.y = base1.y; p1.z = base1.z;

    p2.x = base2.x; p2.y = base2.y; p2.z = base2.z;

    for(int i = 0; i <= steps; i++)
    {
        drawHorizontalLine(p1, p2, color);

        p1.x += dx1;
        p1.y += dy;
        p1.z += dz1;

        p2.x += dx2;
        p2.y += dy;
        p2.z += dz2;
    }
}

void fillTriangle(vec4 p1, vec4 p2, vec4 p3, Gdiplus::Color &color)
{
    //sorting vertices so that p1.y < p2.y < p3.y
    if (p2.y < p1.y)
        std::swap(p2, p1);
    if (p3.y < p1.y)
        std::swap(p3, p1);
    if (p3.y < p2.y)
        std::swap(p3, p2);

    if(p1.y == p2.y)
        fillFlatSideTriangle(p1,p2,p3,color);
    else if(p2.y == p3.y)
        fillFlatSideTriangle(p2,p3,p1,color);
    else
    {
        vec3 p4;//point that lies on p1,p3 and has y equal to p2.y

        float t = (p2.y-p1.y)/(p3.y-p1.y);//coefficient to find x and z of p4

        p4.x = p1.x + (p3.x - p1.x)*t;
        p4.y = p2.y;
        p4.z = p1.z + (p3.z - p1.z)*t;

        fillFlatSideTriangle(p4, p2, p1, color);
        fillFlatSideTriangle(p4, p2, p3, color);
    }
}

//tests vertex coordinates with each side of unit cube
int vertexTest(vec4 &p)
{
    int test = 0;

    test += 0x01 * (p.x > 1);
    test += 0x02 * (p.x < -1);
    test += 0x04 * (p.y > 1);
    test += 0x08 * (p.y < -1);
    test += 0x10 * (p.z > 1);
    test += 0x20 * (p.z < -1);

    return test;
}
//returns
//0 - if triangle is outside unit cube
//1 - inside unit cube
int triangleTest(vec4 &p1,vec4 &p2,vec4 &p3)
{
    int test1 = vertexTest(p1);
    int test2 = vertexTest(p2);
    int test3 = vertexTest(p3);

    if((test1|test2|test3) != 0)
        return 0;
    else
        return 1;
}

void drawMesh(mesh &originalMesh, mat4 &world, mat4 &camera, mat4 &projection, mat4 &viewport)
{
    mesh m;
    copyMesh(originalMesh, m);

    //to world
    for(unsigned int i = 0; i < m.vertices.size(); i++)
        m.vertices[i] = world * m.vertices[i];

    //to camera
    for(unsigned int i = 0; i < m.vertices.size(); i++)
        m.vertices[i] = camera * m.vertices[i];

    //projection
    for(unsigned int i = 0; i < m.vertices.size(); i++)
    {
        m.vertices[i] = projection * m.vertices[i];
        m.vertices[i] = m.vertices[i] / fabs(m.vertices[i].w);
    }

    const int R = m.color.x;
    const int G = m.color.y;
    const int B = m.color.z;

    //triangle
    for(unsigned int i = 0; i < m.indexedTriangles.size(); i++)
    {
        vec4 p1 = m.vertices[m.indexedTriangles[i].vertexIndex[0]];
        vec4 p2 = m.vertices[m.indexedTriangles[i].vertexIndex[1]];
        vec4 p3 = m.vertices[m.indexedTriangles[i].vertexIndex[2]];

        vec3 v1 = (vec3)p2 - p1;
        vec3 v2 = (vec3)p3 - p1;

        float backfacetest = v1.x*v2.y - v1.y*v2.x;
        if(backfacetest<=0)
            continue;

        vec4 triangleNormal = {v1.y*v2.z-v1.z*v2.y,v1.x*v2.z-v1.z*v2.x,v1.x*v2.y-v1.y*v2.x,0};
        triangleNormal = triangleNormal / sqrt(triangleNormal.x*triangleNormal.x + triangleNormal.y*triangleNormal.y + triangleNormal.z*triangleNormal.z);

        vec4 lightNormal = {0,0,1,0};
        float ambietLight = 0.1;
        float lc = triangleNormal * lightNormal * 0.8 + ambietLight;//light coefficient
        if(lc < 0)
            lc = 0;
        Gdiplus::Color triangleColor(255,R*lc,G*lc,B*lc);

        switch(triangleTest(p1,p2,p3))
        {
            case 0:
                break;
            case 1:
                p1 = viewport * p1;
                p2 = viewport * p2;
                p3 = viewport * p3;

                fillTriangle(p1,p2,p3,triangleColor);

                break;
        }
    }
}
