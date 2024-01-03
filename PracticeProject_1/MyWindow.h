#pragma once
#include "MyStd.h"

class MyWindow
{
public:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	RECT m_rtWindow;
	RECT m_rtClientWindow;
	
// ������ ������ �ʿ��� �⺻ �Լ���
public:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

// ������ �ҽ�(MyMain)���� WinMain �� ����ϱ� ���� �۾� (WinMain ���� ȣ��� �Լ���)
public:
	void SetWindow(HINSTANCE hInstance, int nCmdShow);
	void Run();
	void ReleaseAll();

// ���� �ҽ�(MyGameCore)���� �������Ͽ� �� �Լ��� (���� ���ε��� ���� ȣ�� ����)
public:
	virtual bool GameInit() { return true; };
	virtual bool GameFrame() { return true; };
	virtual bool GameRender() { return true; };
	virtual bool GameRelease() { return true; };
};

