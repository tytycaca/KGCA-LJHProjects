#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <d3d11.h>
#include <d3dcompiler.h> 
#include <wrl.h> // windows runtime c++ template library
#include "WicTextureLoader.h" // ../../dxtk/include/ 를 기본 경로로 설정한다. (속성)
#include "MyMath.h"

#pragma comment ( lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

using namespace Microsoft::WRL;

extern UINT		g_xClientSize;
extern UINT		g_yClientSize;
extern double   g_fSecondPerFrame;

class MyBaseCore
{
	virtual void Init() = 0;
	virtual void Frame() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

#define MY_GAME_START(x, y) int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){ Sample myWin; if (myWin.CreateWin(hInstance, x, y)){ myWin.GameRun(); } return 0; }