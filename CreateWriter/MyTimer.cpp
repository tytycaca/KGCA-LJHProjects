#include "MyTimer.h"

void MyTimer::DebugTimer()
{
#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L"FPS=%ld, GameTimer=%10.4f SPF=%d\n",
		m_dwFPS, m_fGameTimeTick,
		m_dwSecondPerFrame);
	OutputDebugString(msgKey);
#endif
}

void MyTimer::Init()
{
	m_dwPreTimeTick = timeGetTime();
	m_dwCurrentTimeTick = 0.0f;
	m_fGameTimeTick = 0.0f;
	m_dwFPS = 0.0f;
}

void MyTimer::Frame()
{
	m_dwCurrentTimeTick = timeGetTime();
	// ����ð�(�ʴ���) = ����ð� - �����ð�
	m_dwSecondPerFrame = m_dwCurrentTimeTick - m_dwPreTimeTick;
	// ����ð�(�и��ʴ���)
	m_fSecondPerFrame = (float)m_dwSecondPerFrame / 1000.0f;
	// ���� ��� �ð�
	m_fGameTimeTick += m_fSecondPerFrame;

	fSecondTime += m_fSecondPerFrame;
	if (fSecondTime >= 1.0f) // 1.01f
	{
		m_dwFPS = iFPS;
		fSecondTime = fSecondTime - 1.0f;
		iFPS = 0;
	}
	iFPS++;

	m_dwPreTimeTick = m_dwCurrentTimeTick;
}