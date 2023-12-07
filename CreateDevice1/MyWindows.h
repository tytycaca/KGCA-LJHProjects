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

// ������ ���� ���� �Լ�
public:
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	ATOM MyRegisterClass(HINSTANCE hInstance);

// WinMain ���ο��� �����ϴ� �Լ� (�ν��Ͻ� ����)
public:
	void SetWindow(HINSTANCE hInst, int nCmdShow);		// ������ �������� Ŭ���� ���, ���� �� ���ν��� �۾�
	void Run();											// ������ ����
	void ReleaseAll(); 

public:
	virtual bool Init() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
};