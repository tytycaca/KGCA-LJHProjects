#pragma once
#include "MyStd.h"

class MyWindow
{
public:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	RECT m_rtWindow;
	RECT m_rtClientWindow;
	
// 윈도우 생성에 필요한 기본 함수들
public:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

// 최하위 소스(MyMain)에서 WinMain 을 사용하기 위한 작업 (WinMain 에서 호출될 함수들)
public:
	void SetWindow(HINSTANCE hInstance, int nCmdShow);
	void Run();
	void ReleaseAll();

// 하위 소스(MyGameCore)에서 재정의하여 쓸 함수들 (동적 바인딩을 통한 호출 구현)
public:
	virtual bool GameInit() { return true; };
	virtual bool GameFrame() { return true; };
	virtual bool GameRender() { return true; };
	virtual bool GameRelease() { return true; };
};

