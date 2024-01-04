#include "MyInput.h"

bool MyInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);

	return true;
}

bool MyInput::Frame()
{
	GetCursorPos(&m_ptMouse); // 화면 좌표
	ScreenToClient(g_hWnd, &m_ptMouse);

	for (DWORD dwKey = 0; dwKey < 256; dwKey++)
	{
		SHORT sKey = ::GetAsyncKeyState(dwKey); 

		// 키 눌림이 감지됐을때
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[dwKey] == KEY_FREE || m_dwKeyState[dwKey] == KEY_UP)
				m_dwKeyState[dwKey] = KEY_PUSH;
			else
				m_dwKeyState[dwKey] = KEY_HOLD;
		}
		else
		{
			if (m_dwKeyState[dwKey] == KEY_PUSH || m_dwKeyState[dwKey] == KEY_HOLD)
				m_dwKeyState[dwKey] == KEY_UP;
			else
				m_dwKeyState[dwKey] == KEY_FREE;
		}
	}

	return true;
}

bool MyInput::Render()
{
	return true;
}

bool MyInput::Release()
{
	return true;
}
