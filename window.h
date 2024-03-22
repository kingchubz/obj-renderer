#pragma once

#define CLASS_NAME "window class"
#define WIN_NAME "3drenderer"


#include <windows.h>
#include <winuser.h>

#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

using namespace Gdiplus;



#include "input.h"

HWND initWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int width, int height);
bool processMessage();
LRESULT CALLBACK handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
