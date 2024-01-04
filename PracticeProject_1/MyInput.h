#pragma once
#include <windows.h>
#include "MyStd.h"

enum { KEY_FREE = 0, KEY_PUSH, KEY_HOLD, KEY_UP };

class MyInput
{
public:
	POINT	m_ptMouse;
	DWORD    m_dwKeyState[256];
	static MyInput& Get()
	{
		static MyInput mgr;
		return mgr;
	}

public:
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();

private:
	MyInput() {};

public:
	~MyInput()
	{
		Release();
	}
};