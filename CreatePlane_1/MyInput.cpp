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
	// ȭ�� ��ǥ�踦 ��ȯ�Ѵ�.
	GetCursorPos(&m_ptMousePos);
	// Ŭ���̾�Ʈ ��ǥ�踦 ��ȯ�Ѵ�.
	ScreenToClient(hWnd, &m_ptMousePos);

	for (int iKey = 0; iKey < 255; iKey++)
	{
		// iKey�� �ش��ϴ� Ű�� ���¸� ��ȯ�ް�
		SHORT sKey = GetAsyncKeyState(iKey);

		// 8     0     0     0
		// 1000  0000  0000  0000
		//			 &
		// 1000  0000  0000  0000
		if (sKey & 0x8000) // ������
		{
			// ���� �����ӿ���
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
		else // ���� �����ӿ����� �������� �ʾҴ�
		{
			// ���� �����ӿ���
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
