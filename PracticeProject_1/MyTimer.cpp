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
	DWORD dwElapseTick = m_dwTickEnd - m_dwTickStart; // ��� �ð�

	g_fSecPerFrame = m_fSecondPerFrame = dwElapseTick / 1000.0f; // 1�������� ó���ϴµ� �ɸ� �ð� (ms)
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
	m_outmsg = L"���Ӱ���ð�: ";
	m_outmsg += std::to_wstring(m_fGameTimer);
	m_outmsg += L" ";
	m_outmsg += L"1������ ����ð�: ";
	m_outmsg += std::to_wstring(m_fFramePerSecond);
	m_outmsg += L" ";
	m_outmsg += L"�ʴ� ������: ";
	m_outmsg += m_msgFPS;
	m_outmsg += L"\n";
	
	OutputDebugString(m_outmsg.c_str());

	return true;
}

bool MyTimer::Release()
{
	return true;
}
