//****************************************************************************************************************
//
//  File        :   VHTestGame.cpp
//
//  Content     :   Win32 skeleton for Mathteroids code examination mini-project
//
//  (c) 2007-2013 Applied Research Associates, Inc.
//
//****************************************************************************************************************

#include <windows.h>  
#include <winuser.h>
#include <mmsystem.h>
#include <set>
#include <time.h>

#include "Controller.h"

#include "Const.h"


// Some drawing tools
HBITMAP hbmMap;
HDC hdcMap;

HBITMAP hbmDrawSurface;
HDC hdcBackBuffer = NULL;
HWND G_hwnd;

Controller* controller = NULL;


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void Update(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pszCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG  msg;
    WNDCLASS wndClass;
    nCmdShow = SW_SHOWNORMAL;
    pszCmdLine = NULL;
    hPrevInstance = NULL;
    char *szAppName = "Mathteroids! (c) 2007-2013 Applied Research Associates, Inc.\0";

    wndClass.style              = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
    wndClass.lpfnWndProc        = WindowProc;
    wndClass.cbClsExtra         = 0;
    wndClass.cbWndExtra         = 0;
    wndClass.hInstance          = hInstance;
    wndClass.hIcon              = LoadIcon(NULL, 0);
    wndClass.hCursor            = LoadCursor(NULL, IDC_CROSS);
    wndClass.hbrBackground      = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName       = NULL;
    wndClass.lpszClassName      = szAppName;
    
    if (RegisterClass(&wndClass) == 0)
	{
        return 0;
	}

    if ((hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                            CW_USEDEFAULT, CW_USEDEFAULT, 
									 SCREEN_SIZE[X] + SCREEN_ERROR[X], SCREEN_SIZE[Y] + SCREEN_ERROR[Y],
                            NULL, NULL, hInstance, NULL)) == 0)
	{
        return 0;
	}

	G_hwnd = hwnd;
	
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
   
	// The main message loop
	bool fReturnVal = true;
	while (GetMessage(&msg, NULL, 0, 0) && fReturnVal) 
	{
		if (msg.message == WM_QUIT)
			fReturnVal = false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static int x, y;
	static HINSTANCE hInstance;

	switch (msgId)
	{
		// Construct
		case WM_CREATE:
		{
			controller = new Controller();

         hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
			hdc = GetDC(hwnd);

			hdcBackBuffer = CreateCompatibleDC(hdc);
			hbmDrawSurface = CreateCompatibleBitmap(hdc, SCREEN_SIZE[X], SCREEN_SIZE[Y]);
			SelectObject(hdcBackBuffer, hbmDrawSurface);

			hdcMap = CreateCompatibleDC(hdc);
			hbmMap = CreateCompatibleBitmap(hdc, SCREEN_SIZE[X], SCREEN_SIZE[Y]);
			SelectObject(hdcMap, hbmMap);

			ReleaseDC(hwnd, hdc);

			UINT timerId = SetTimer(hwnd, 1, UPDATE_TIME, NULL);
			return 0;
		}
		
		// Deconstruct
		case WM_DESTROY:
      {
			delete controller;

			DeleteObject(hbmDrawSurface);
			DeleteDC(hdcBackBuffer);

			PostQuitMessage(0);
			return 0;
		}

		// Draw
		case WM_TIMER:
		{
			Update();
			return 0;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT paintStruct;
			hdc = BeginPaint(hwnd, &paintStruct);
			EndPaint(hwnd, &paintStruct);
			ReleaseDC(hwnd, hdc);
			return 0;
		}
        
		// Input
      case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
			return 0;

		case WM_LBUTTONDOWN:
		{
			controller->input(SHOOT);
			return 0;
		}


		case WM_KEYDOWN:
		{
			switch (wParam)
         {
			case VK_SPACE:
				controller->input(SHOOT);
				break;
			case VK_LEFT:
				controller->input(CCW_ROT);
				break;
			case VK_RIGHT:
				controller->input(CC_ROT);
				break;
			case VK_UP:
				controller->input(UP);
				break;
			case VK_DOWN:
				controller->input(DOWN);
				break;
			}
			
			return 0;
		}

		case WM_KEYUP:
		{
			switch (wParam)
         {
			case VK_LEFT:
				controller->input(STOP_ROT);
				break;
			case VK_RIGHT:
				controller->input(STOP_ROT);
				break;
			}	

			return 0;
		}

		case WM_CHAR:
		{
			switch (wParam)
			{
			case 'q':
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}

		default:
			return DefWindowProc(hwnd, msgId, wParam, lParam);
	}
}

// Draw loop
void Update(void)
{
    HDC hdc = GetDC(G_hwnd);
	if (hdc)
	{
		controller->draw(hdcBackBuffer);

		// "Swap buffers"
		BitBlt(hdc, 0, 0, SCREEN_SIZE[X], SCREEN_SIZE[Y], hdcBackBuffer, 0, 0, SRCCOPY );
	}
    ReleaseDC(G_hwnd, hdc);
}


