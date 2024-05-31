#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>

class MyBaseCore
{
	virtual void Init() = 0;
	virtual void Frame() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

#define MY_GAME_START(x, y) int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){ Sample myWin; if (myWin.CreateWin(hInstance, x, y)){ myWin.GameRun(); } return 0; }