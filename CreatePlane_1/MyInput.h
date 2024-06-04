#pragma once
#include <Windows.h>
#include <tchar.h>

enum KeyState
{
	KEY_FREE = 0,		// ����
	KEY_UP,				// �ٷ� �����ٰ� ���»���
	KEY_PUSH,			// ���»��¿��� ������ ��
	KEY_HOLD,			// ������ ���� �� (������ ������ ���ݵ� �����ִ� ����)
};

class MyInput
{
private:
	DWORD m_dwKeyState[256];
	POINT m_ptMousePos;

public:
	void DebugPrint(int iKey);
	void DebugMousePos();
	void Frame(HWND hWnd);
	DWORD KeyCheck(DWORD dwKey);
	void KeyTest();

public:
	MyInput()
	{
		ZeroMemory(&m_dwKeyState, sizeof(DWORD));
	}
};