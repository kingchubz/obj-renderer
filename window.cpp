#include "window.h"

RECT wndRect;
int wndcntrX = 1, wndcntrY = 1;

HWND initWindow(
                HINSTANCE hInstance,
                HINSTANCE hPrevInstance,
                LPSTR lpCmdLine,
                int nCmdShow,
                int width, int height
                )
{
    //Creating window
    WNDCLASS wc = {};

    wc.lpfnWndProc = handleMessage; //callback function
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
                  0,
                  CLASS_NAME,           //class name
                  WIN_NAME,             //title
                  WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX,  //style
                  CW_USEDEFAULT,        //x
                  CW_USEDEFAULT,        //y
                  width+6,              //plus pixels because window panel takes up 6 pixel of width
                  height+29,            //plus pixels because window panel takes up 29 pixel of height
                  NULL,                 //handle to parent window
                  NULL,                 //handle to child/menu
                  hInstance,            //handle to instance of the module assosiated with the window
                  NULL                  //A pointer to a value to be passed to the window through the CREATESTRUCT structure
                  );

    if(hwnd == NULL)
    {
        MessageBox( nullptr, "Cannot create main window.", "Error",MB_OK );
        return nullptr;
    }

    //setting up input devices
    RAWINPUTDEVICE Rid[1];

    Rid[0].usUsagePage = 0x01;
    Rid[0].usUsage = 0x02;
    Rid[0].dwFlags = 0;
    Rid[0].hwndTarget = hwnd;

    if (RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])) == false)
    {
        MessageBox(nullptr, "Cannot access input device.", "Error", MB_OK);
        return nullptr;
    }

    GetWindowRect(hwnd, &wndRect);

    //Displaying window to user
    ShowWindow(hwnd,SW_SHOWDEFAULT);

    return hwnd;
}

bool processMessage()
{
    MSG msg = {};

    while( PeekMessage(&msg,nullptr,0,0,PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if(msg.message == WM_QUIT)
            return false;
    }

    return true;
}

LRESULT CALLBACK handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INPUT:
        {
            UINT dwSize;

            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
                sizeof(RAWINPUTHEADER));

            LPBYTE lpb = new BYTE[dwSize];
            if (lpb == NULL)
            {
                break;
            }

            if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
                OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

            RAWINPUT* raw = (RAWINPUT*)lpb;

            raw->data.mouse.usButtonFlags;
            input::mouse::relativeX = raw->data.mouse.lLastX;
            input::mouse::relativeY = raw->data.mouse.lLastY;

            delete[] lpb;
        }
        break;

        //window close
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        //keyboard
        case WM_KEYDOWN:
            input::keyboard::keystates[(int)wParam] = true;
            break;

        case WM_KEYUP:
            input::keyboard::keystates[(int)wParam] = false;
            break;

        //mouse
        case WM_MOUSEMOVE:
            ClipCursor(&wndRect);

            input::mouse::x = LOWORD(lParam);
            input::mouse::y = HIWORD(lParam);

            ShowCursor(false);
            break;

        case WM_LBUTTONDOWN:
            input::mouse::leftButton = true;
            break;

        case WM_LBUTTONUP:
            input::mouse::leftButton = false;
            break;

        case WM_RBUTTONDOWN:
            input::mouse::rightButton = true;
            break;

        case WM_RBUTTONUP:
            input::mouse::rightButton = false;
            break;
        case WM_MOVE:
        case WM_SIZE:
            GetWindowRect(hwnd, &wndRect);
            wndcntrX = (wndRect.left+wndRect.right)/2;
            wndcntrY = (wndRect.bottom+wndRect.top)/2;
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
