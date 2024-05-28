#include "MyWindow.h"

const wchar_t CLASS_NAME[] = L"SAMPLEWINDOW";		// �̸�

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

void MyWindow::CreateRegisterClass(HINSTANCE hInstance)
{
	// 1. ������ Ŭ������ �ü���� ����ؾ� �Ѵ�.
	// ������ ����ü�� ä���� ����Ѵ�.
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;		// ���ּ�(�Ǵ� ��ȭ��ȣ)
	wc.hInstance = hInstance;			// �ֹι�ȣ
	wc.lpszClassName = CLASS_NAME;		// �̸�
	RegisterClass(&wc);

	m_hInstance = hInstance;
}

bool MyWindow::CreateWin(UINT xSize, UINT ySize)
{
	// 2) ��ϵ� ������Ŭ������ ����Ͽ� ������ ����
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
	// �޼���ť�� ����ִ� ��� �޼����� ���۾����� ���ν����� �����Ѵ�.
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
			// ���� ������ �����Ѵ�. 1������
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
			PostQuitMessage(0); // WM_QUIIT �޼����� �޼���ť�� �����
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}