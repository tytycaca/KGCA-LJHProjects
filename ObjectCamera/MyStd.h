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
//../../dxtk/include  기본경로로 설정한다. (속성)
#include "WicTextureLoader.h"
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
extern double   g_fGameTime;

class MyBaseCore
{
	virtual void Init() = 0;
	virtual void Frame() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

#define SAMPLE_CREATE class Sample : public MyCore {
#define SAMPLE_END };
#define T_GAME_START(x, y) int WINAPI wWinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance,PWSTR pCmdLine,int nCmdShow){	Sample win;	if (win.CreateWin(hInstance, x, y))	{		win.GameRun();	}	return 0;}
#define T_GAME(x,y)  SAMPLE_CREATE SAMPLE_END T_GAME_START(x,y)