#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <sti.h>
#include <gdiplus.h>
using namespace Gdiplus;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("HelloMouse20160702");

HWND hWnd;

TCHAR pointStr[32];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS myProg;
	if (!hPreInst) {
		myProg.style			= CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc		= WndProc;
		myProg.cbClsExtra		= 0;
		myProg.cbWndExtra		= 0;
		myProg.hInstance		= hInstance;
		myProg.hIcon			= NULL;
		myProg.hCursor			= LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		myProg.lpszMenuName		= NULL;
		myProg.lpszClassName	= szClassName;
		if (!RegisterClass(&myProg)) { return FALSE; }
	}
	hWnd = CreateWindow(szClassName,	// class名
		_T("Hello Mouse !! 左クリックすると座標が表示されます！"),		// タイトル
		WS_OVERLAPPEDWINDOW,		// Style
		CW_USEDEFAULT,				// X
		CW_USEDEFAULT,				// Y
		CW_USEDEFAULT,				// Width
		CW_USEDEFAULT,				// Height
		NULL,						// 親ウィンドウまたはオーナーウィンドウのハンドル
		NULL,						// メニューハンドルまたは子ウィンドウ ID
		hInstance,					// アプリケーションインスタンスのハンドル
		NULL						// ウィンドウ作成データ
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static unsigned short x = 0;
	static unsigned short y = 0;

	switch (msg) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd , &ps);

			SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			
			SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			TextOut(hdc, x, y, pointStr, _tcslen(pointStr));

			EndPaint(hWnd , &ps);
			break;
		case WM_LBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			memset(pointStr , NULL, 32);
			_stprintf_s(pointStr, 32, _T("(%d, %d)"), x, y);
			InvalidateRect(hWnd , 0 , true);
			break;
		case WM_CREATE:
			memset(pointStr , NULL, 32);
			_stprintf_s(pointStr, 32, _T("マウスで左クリック！"));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}
