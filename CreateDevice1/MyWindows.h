#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <map>

class MyWindows
{
public:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;

// 윈도우 생성 관련 함수
public:
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	ATOM MyRegisterClass(HINSTANCE hInstance);

// WinMain 내부에서 동작하는 함수 (인스턴스 관리)
public:
	void SetWindow(HINSTANCE hInst, int nCmdShow);		// 윈도우 레지스터 클래스 등록, 생성 및 프로시져 작업
	void Run();											// 렌더링 루프
	void ReleaseAll(); 

public:
	virtual bool Init() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
};