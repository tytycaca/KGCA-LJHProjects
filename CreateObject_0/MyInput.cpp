#include "MyInput.h"

void MyInput::DebugPrint(int iKey)
{
#ifdef _DEBUG
	static int iPushCounter = 0;
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey, L"KEY=%d(%d)\n", iKey, iPushCounter++);
	OutputDebugString(msgKey);
#endif
}

void MyInput::DebugMousePos()
{
#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey, L"Mouse X=%d, Y=%d\n",
		m_ptMousePos.x, m_ptMousePos.y);
	OutputDebugString(msgKey);
#endif
}

void MyInput::Frame(HWND hWnd)
{
	// 화면 좌표계를 반환한다.
	GetCursorPos(&m_ptMousePos);
	// 클라이언트 좌표계를 반환한다.
	ScreenToClient(hWnd, &m_ptMousePos);

	for (int iKey = 0; iKey < 255; iKey++)
	{
		// iKey에 해당하는 키의 상태를 반환받고
		SHORT sKey = GetAsyncKeyState(iKey);

		// 8     0     0     0
		// 1000  0000  0000  0000
		//			 &
		// 1000  0000  0000  0000
		if (sKey & 0x8000) // 눌렀다
		{
			// 이전 프레임에서
			if (m_dwKeyState[iKey] == KEY_FREE ||
				m_dwKeyState[iKey] == KEY_UP)
			{
				m_dwKeyState[iKey] = KEY_PUSH;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_HOLD;
			}
		}
		else // 현재 프레임에서는 눌러지지 않았다
		{
			// 이전 프레임에서
			if (m_dwKeyState[iKey] == KEY_PUSH ||
				m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_FREE;
			}
		}
	}
}

DWORD MyInput::KeyCheck(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}

void MyInput::KeyTest()
{
	if (m_dwKeyState[VK_HOME] == KEY_PUSH)
	{
		DebugPrint(KEY_PUSH);
	}
	if (m_dwKeyState[VK_HOME] == KEY_HOLD)
	{
		DebugPrint(KEY_HOLD);
	}
	if (m_dwKeyState[VK_HOME] == KEY_UP)
	{
		DebugPrint(KEY_UP);
	}
}
