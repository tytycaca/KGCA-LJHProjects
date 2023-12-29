#pragma once
#include "MyWindow.h"

class MyDevice : public MyWindow
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;

public:
	bool CreateDevice();
	bool DeleteDevice();
};

