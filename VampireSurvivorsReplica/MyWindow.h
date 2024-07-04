#pragma once
#include "MyStd.h"
class MyWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool        m_isActive;
	
	RECT		m_rtWindow;
	RECT		m_rtClient;
public:
	void   CreateRegisterClass(HINSTANCE hInstance);
	bool   CreateWin(HINSTANCE hInstance, UINT xSize = 1280, UINT ySize = 720);
	bool   WindowRun();
	MyWindow();
};

