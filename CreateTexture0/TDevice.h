#pragma once
#include "TWindow.h"
#include <d3d11.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <d3dcompiler.h>
#include <memory>

// 프로젝트 속성에 링커에 입력에 추가종속성 d3d11.lib; d3dcompiler.lib; DirectXTex.lib;
// 넣어놨던 것을 #pragma comment 을 이용하면 프로젝트로 포함할 수 있다.
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

class TDevice : public TWindow
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
public:
	virtual bool    Init() { return true; };
	virtual bool    Render() { return true; };
	virtual bool    Release() { return true; };

	virtual bool	GameInit() override;
	virtual bool	GameRender()override;
	virtual bool	GameRelease()override;
};

