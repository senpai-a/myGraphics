#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "myGraphics.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int x, y;
long c;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t className[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		className,                     // Window class
		L"����",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	
	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		if (MessageBox(hwnd, L"ȷ���˳�?", L"�˳�...", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		//Ϳ�ڱ���
		RECT fullRect;
		fullRect.bottom = 0;
		fullRect.left = 0;
		fullRect.right = 2560;
		fullRect.top = 1080;
		FillRect(hdc, &fullRect, CreateSolidBrush(RGB(0, 0, 0)));
				
		//����
		for (int i = 0; i <= 600; i += 100) {
			drawLine(hdc, 300, 300, 600, i, RGB(i, 0, 255));
			drawLine(hdc, 300, 300, 0, i, RGB(i, 255, 0));
			drawLine(hdc, 300, 300, i, 0, RGB(0, i, 255));
			drawLine(hdc, 300, 300, i, 600, RGB(255, i, 0));
		}

		drawCircle(hdc, 300, 300, 200, RGB(255, 100, 100));
		drawCircle1(hdc, 300, 300, 250, RGB(100, 100, 255));
		for(int i=40;i<=400;i+=40)
			drawEllipse(hdc, 700, 200+2*(i-100), i, 50, RGB(100, (i-200)*2, 50));
		for (int i = 40; i <=400; i += 40)
			drawEllipse(hdc, 200 + 2 * (i - 100), 700, 50, i, RGB((i - 200) * 2, 50, 100));
		
		for (int i = 201; i <= 202; i += 100) {
			fillDFS(hdc, 200, i, RGB(i/2, 0, 255-i/2));
		}

		std::vector<IVector2> v;
		v.emplace_back(25, 25);
		v.emplace_back(75, 50);
		v.emplace_back(100, 50);
		v.emplace_back(100, 75);
		v.emplace_back(125, 75);
		v.emplace_back(125, 100);
		v.emplace_back(75, 75);
		v.emplace_back(100, 125);
		v.emplace_back(75, 125);
		v.emplace_back(50, 125);
		v.emplace_back(50, 100);
		v.emplace_back(50, 75);
		fillPolygon(hdc, v, RGB(2, 100, 200));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
