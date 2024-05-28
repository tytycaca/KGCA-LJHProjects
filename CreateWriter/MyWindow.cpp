#include "MyWindow.h"
// ������ ���ν������� �� Ŭ������ ����ϱ� ���� ���
MyWindow* g_pWindow = nullptr;

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

bool MyWindow::CreateWin(HINSTANCE hInstance, UINT xSize, UINT ySize)
{
	CreateRegisterClass(hInstance);
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

bool MyWindow::WindowRun()
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
			return true;
		}
	}
	return false;
}

MyWindow::MyWindow()
{
	// ������ ���ν������� �� Ŭ������ ����ϱ� ���� ���
	g_pWindow = this;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	{
		switch (uMsg)
		{
		// ���α׷��� Ȱ��ȭ(��Ŀ��)
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
			PostQuitMessage(0); // WM_QUIIT �޼����� �޼���ť�� �����
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}