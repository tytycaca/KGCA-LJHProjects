#pragma once
#include "MyWindow.h"
#include <d3d11.h> // DirectX 기능
#pragma comment (lib, "d3d11.lib")
//#include <d3d11.h> // DirectX 기능
// 1번 방법: 속성 -> 링커 -> 입력 -> 추가종속성 -> d3d11.lib 추가
// 2번 방법: #pragma comment ( lib, "d3d11.lib" )
// 양쪽으로 다 해놔도 상관없다.
//#pragma comment (lib, "d3d11.lib")

class MyDevice : public MyWindow
{
public:
	// 인터페이스 획득 (할당, 생성)
	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	ID3D11RenderTargetView* g_pRTV = nullptr;	// 화면을 어디에 뿌릴지 결정

	bool CreateDevice(HWND hWnd);
	void DeleteDevice();

	virtual void GameRun() override;
};