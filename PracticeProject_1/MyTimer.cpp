#include "MyTimer.h"

float g_fSecPerFrame = 0.0f;

bool MyTimer::Init()
{
	m_dwTickStart = timeGetTime();

	return true;
}

bool MyTimer::Frame()
{
	m_dwTickEnd = timeGetTime();
	DWORD dwElapseTick = m_dwTickEnd - m_dwTickStart; // 경과 시간

	g_fSecPerFrame = m_fSecondPerFrame = dwElapseTick / 1000.0f; // 1프레임을 처리하는데 걸린 시간 (ms)
	m_fGameTimer += m_fSecondPerFrame;

	m_iFPS++;
	m_dwTime += dwElapseTick;
	if (m_dwTime >= 1000)
	{
		m_msgFPS = std::to_wstring(m_iFPS);
		m_msgFPS += L" FPS";
		m_dwTime -= 1000;
		m_iFPS = 0;
	}

	m_dwTickStart = m_dwTickEnd;

	return true;
}

bool MyTimer::Render()
{
	m_outmsg.clear();
	m_outmsg = L"게임경과시간: ";
	m_outmsg += std::to_wstring(m_fGameTimer);
	m_outmsg += L" ";
	m_outmsg += L"1프레임 경과시간: ";
	m_outmsg += std::to_wstring(m_fFramePerSecond);
	m_outmsg += L" ";
	m_outmsg += L"초당 프레임: ";
	m_outmsg += m_msgFPS;
	m_outmsg += L"\n";
	
	OutputDebugString(m_outmsg.c_str());

	return true;
}

bool MyTimer::Release()
{
	return true;
}
