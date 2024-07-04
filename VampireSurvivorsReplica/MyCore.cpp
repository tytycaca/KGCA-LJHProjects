#include "MyCore.h"
bool		 g_bGameRun = true;

HRESULT  MyCore::SetAlphaBlendState()
{
	HRESULT hr;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	bd.AlphaToCoverageEnable = FALSE;//discard;같은 결과.
	bd.IndependentBlendEnable = FALSE;
	//D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
	// 백버퍼의 컬러값(DestBlend) 과  현재 출력 컬러(SrcBlend)값을 혼합연산한다.
	bd.RenderTarget[0].BlendEnable = TRUE;
	// RGA 컬러값 연산( 기본 알파블랭딩 공식) 알파범위( 0 ~ 1 )
	// 최종 컬러값 = 소스컬러*소스알파 	+  데스크컬러* (1.0 - 소스알파)
	//  정점위치 = 목적지위치*S + 현재위치* (1- S); S=0, S=0.5, S = 1
	// 
	// 만약 소스컬러 = 1,0,0,1(빨강)   배경컬러 = 0,0,1,1(파랑)
	// 1)소스알파 = 1.0F ( 완전불투명)
		// RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
		// 최종 컬러값 = 빨강*1.0F 	+  파랑* (1.0 - 1.0F)
		// ->최종 컬러값(소스색) = [1,0,0] 	+  [0,0,0]
	// 2)소스알파 = 0.0F ( 완전투명)
		// RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
		// 최종 컬러값 = 빨강*0.0F 	+  파랑* (1.0 - 0.0F)
		// ->최종 컬러값(배경색) = [0,0,0] +  [0,0,1]
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// A 알파값 연산
	// A = SRC Alpha*1 + DestAlpha*0;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = MyDevice::m_pd3dDevice->CreateBlendState(&bd, m_pAlphaBlend.GetAddressOf());
	if (SUCCEEDED(hr))
	{
		MyDevice::m_pContext->OMSetBlendState(m_pAlphaBlend.Get(), 0, -1);
	}
	return hr;
}

void MyCore::Init(){}
void MyCore::Frame() {}
void MyCore::Render() {}
void MyCore::Release() {}

void   MyCore::GamePreFrame()
{ 
	m_Timer.Frame();
	if (m_isActive)
	{
		I_Input.Frame(m_hWnd);
	}
	I_Sound.Frame();
}
void   MyCore::GameFrame()
{
	GamePreFrame();
	Frame();
	GamePostFrame();
}
void   MyCore::GamePostFrame()
{
}
void  MyCore::GamePreRender()
{
	float clearColor[] = { 0.3640f, 0.4543545322f, 0.645672321f, 1.0f };
	MyDevice::m_pContext->ClearRenderTargetView(MyDevice::m_pRTV, clearColor);

	MyDevice::m_pContext->OMSetRenderTargets(1, &MyDevice::m_pRTV, nullptr);
	MyDevice::m_pContext->RSSetViewports(1, &MyDevice::m_ViewPort);
	MyDevice::m_pContext->OMSetBlendState(m_pAlphaBlend.Get(), 0, -1);
}
void  MyCore::GamePostRender()
{
	m_font.DrawText(m_Timer.m_csBuffer, { 0,0 });
	MyDevice::m_pSwapChain->Present(0, 0);
}
void   MyCore::GameRender()
{
	GamePreRender();
	Render();
	GamePostRender();
	DebugRender();
}
void   MyCore::DebugRender()
{
	/*m_Timer.DebugTimer();
	I_Input.DebugMousePos();
	I_Input.KeyTest();*/
	I_Sound.Render();
}
void   MyCore::GameInit()
{
	// 그래픽 처리를 위한 초기화 작업
	if (MyDevice::CreateDevice(m_hWnd))
	{
		I_Tex.Set(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext);
		I_Shader.Set(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext);
		SetAlphaBlendState();

		I_Sound.Set(nullptr, nullptr);
		I_Sprite.Load(L"../../resource/SpriteInfo.txt");

		m_font.Init();
		// 3D 백버퍼를 얻어서 전달해야 한다.
		IDXGISurface* dxgiSurface = nullptr;
		MyDevice::m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
			(void**)&dxgiSurface);
		m_font.ResetDevice(dxgiSurface);
		dxgiSurface->Release();
	}
	Init();
}
void   MyCore::GameRun()
{
	GameInit();
	while(g_bGameRun)
	{
		if(MyWindow::WindowRun()==false)
		{
			break;
		}
		GameFrame();
		GameRender();
	}
	GameRelease();
}

void   MyCore::GameRelease()
{
	Release();

	I_Sound.Release();
	I_Shader.Release();
	I_Tex.Release();

	m_font.Release();
	MyDevice::DeleteDevice();
}