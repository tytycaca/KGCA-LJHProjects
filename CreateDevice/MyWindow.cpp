#include "MyWindow.h"

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

bool MyWindow::CreateWin(UINT xSize, UINT ySize)
{
	// 2) 등록된 윈도우클래스를 사용하여 윈도우 생성
	HWND hwnd = CreateWindowEx(
		0, // Optional window styles.
		CLASS_NAME, // Window class
		L"Learn to Program Windows", // Window text
		WS_OVERLAPPEDWINDOW, // Window style
		// Size and position
		0, 0, xSize, ySize,
		NULL, // Parent window
		NULL, // Menu
		m_hInstance, // Instance handle
		NULL // Additional application data
	);
	if (hwnd == NULL)
	{
		return 0;
	}
	m_hWnd = hwnd;
	ShowWindow(hwnd, SW_SHOW);

	return true;
}

void MyWindow::WindowRun()
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
			// 게임 로직을 가동한다. 1프레임
			GameRun();
		}
	}
}

void   MyWindow::GameRun()
{

}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0); // WM_QUIIT 메세지를 메세지큐에 등록함
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}