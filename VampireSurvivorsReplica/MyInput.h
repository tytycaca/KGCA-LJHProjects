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
public:
	static MyInput& Get()
	{
		static MyInput mgr;
		return mgr;
	}
private:
	DWORD   g_dwKeyState[256];
public:	
	POINT   m_ptMousePos;
public:
	void    DebugPrint(int iKey);
	void    DebugMousePos();
	void    Frame(HWND hWnd);
	DWORD   KeyCheck(DWORD dwKey);
	void    KeyTest();
private:
	MyInput()
	{
		ZeroMemory(&g_dwKeyState, sizeof(DWORD) * 256);
	}
};

#define I_Input MyInput::Get()