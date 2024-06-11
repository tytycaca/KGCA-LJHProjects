#pragma once
#include <windows.h>
#include <tchar.h>
enum KeyState
{
	KEY_FREE = 0,	// ����
	KEY_UP,			// �ٷ� �����ٰ� ���»���
	KEY_PUSH,		// ���»��¿��� ������ ��
	KEY_HOLD,		// ����� ���� ��(������ ������ ���ݵ� ������.)
};

class MyInput
{
private:
	DWORD   g_dwKeyState[256];
	POINT   m_ptMousePos;
public:
public:
	void    DebugPrint(int iKey);
	void    DebugMousePos();
	void    Frame(HWND hWnd);
	DWORD   KeyCheck(DWORD dwKey);
	void    KeyTest();
public:
	MyInput()
	{
		ZeroMemory(&g_dwKeyState, sizeof(DWORD) * 256);
	}
};
