#pragma once
#include <Windows.h>
#include <string>
// #pragma comment (lib, "winmm.lib") // timeGetTime

class MyTimer
{
public:
	float m_fGameTimer = 0.0f;
	float m_fFramePerSecond = 0.0f;
	float m_fSecondPerFrame = 0.0f;

public:
	UINT m_iFPS = 0;
	DWORD m_dwTime = 0.0f;
	DWORD m_dwTickStart;
	DWORD m_dwTickEnd;
	std::wstring m_msgFPS;
	std::wstring m_outmsg;

public:
	bool Init();
	bool Frame();
	// 출력 테스트용
	bool Render();
	bool Release();
};

