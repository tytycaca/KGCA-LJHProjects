#include "MyWindow.h"
// 윈도우 프로시져에서 내 클래스를 사용하기 위한 편법
MyWindow* g_pWindow = nullptr;

UINT g_xClientSize;
UINT g_yClientSize;

const wchar_t CLASS_NAME[] = L"SAMPLEWINDOW";		// 이름

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

void MyWindow::CreateRegisterClass(HINSTANCE hInstance)
{
	// 1. 윈도우 클래스를 운영체제에 등록해야 한다.
	// 지정된 구조체를 채워서 등록한다.
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;		// 집주소(또는 전화번호)
	wc.hInstance = hInstance;			// 주민번호
	wc.lpszClassName = CLASS_NAME;		// 이름
	RegisterClass(&wc);

	m_hInstance = hInstance;
}

bool MyWindow::CreateWin(HINSTANCE hInstance, UINT xSize, UINT ySize)
{
	g_xClientSize = xSize;
	g_yClientSize = ySize;

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	// 추가 : 클라이언트 크기를 xSize, ySize 로 조정한다.
	RECT rt = { 0,0,xSize,ySize };
	AdjustWindowRect(&rt, dwStyle, FALSE);

	CreateRegisterClass(hInstance);
	// 2) 등록된 윈도우클래스를 사용하여 윈도우 생성
	HWND hwnd = CreateWindowEx(
		0, // Optional window styles.
		CLASS_NAME, // Window class
		L"Learn to Program Windows", // Window text
		dwStyle, // Window style
		// Size and position
		0, 0,
		rt.right - rt.left,
		rt.bottom - rt.top,
		NULL, // Parent window
		NULL, // Menu
		m_hInstance, // Instance handle
		NULL // Additional application data
	);
	if (hwnd == NULL)
	{
		return 0;
	}

	GetClientRect(hwnd, &m_rtWindow);
	GetClientRect(hwnd, &m_rtClient);

	m_hWnd = hwnd;
	ShowWindow(hwnd, SW_SHOW);

	return true;
}

bool MyWindow::WindowRun()
{
	// 메세지큐에 담겨있는 모든 메세지를 수작업으로 프로시져에 전달한다.
	MSG msg = { };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return true;
		}
	}
	return false;
}

MyWindow::MyWindow()
{
	// 윈도우 프로시져에서 내 클래스를 사용하기 위한 편법
	g_pWindow = this;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	{
		switch (uMsg)
		{
		// 프로그램의 활성화(포커스)
		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				if(g_pWindow != nullptr)
					g_pWindow->m_isActive = false;
			}
			else
			{
				if (g_pWindow != nullptr)
					g_pWindow->m_isActive = true;
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0); // WM_QUIIT 메세지를 메세지큐에 등록함
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}