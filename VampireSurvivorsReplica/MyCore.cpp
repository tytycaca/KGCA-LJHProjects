#include "MyCore.h"
bool		 g_bGameRun = true;
bool		 g_bGamePause = false;

HRESULT  MyCore::SetAlphaBlendState()
{
	HRESULT hr;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	bd.AlphaToCoverageEnable = FALSE;//discard;���� ���.
	bd.IndependentBlendEnable = FALSE;
	//D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
	// ������� �÷���(DestBlend) ��  ���� ��� �÷�(SrcBlend)���� ȥ�տ����Ѵ�.
	bd.RenderTarget[0].BlendEnable = TRUE;
	// RGA �÷��� ����( �⺻ ���ĺ��� ����) ���Ĺ���( 0 ~ 1 )
	// ���� �÷��� = �ҽ��÷�*�ҽ����� 	+  ����ũ�÷�* (1.0 - �ҽ�����)
	//  ������ġ = ��������ġ*S + ������ġ* (1- S); S=0, S=0.5, S = 1
	// 
	// ���� �ҽ��÷� = 1,0,0,1(����)   ����÷� = 0,0,1,1(�Ķ�)
	// 1)�ҽ����� = 1.0F ( ����������)
		// RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
		// ���� �÷��� = ����*1.0F 	+  �Ķ�* (1.0 - 1.0F)
		// ->���� �÷���(�ҽ���) = [1,0,0] 	+  [0,0,0]
	// 2)�ҽ����� = 0.0F ( ��������)
		// RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
		// ���� �÷��� = ����*0.0F 	+  �Ķ�* (1.0 - 0.0F)
		// ->���� �÷���(����) = [0,0,0] +  [0,0,1]
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// A ���İ� ����
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
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	MyDevice::m_pContext->ClearRenderTargetView(MyDevice::m_pRTV, clearColor);

	MyDevice::m_pContext->OMSetRenderTargets(1, &MyDevice::m_pRTV, nullptr);
	MyDevice::m_pContext->RSSetViewports(1, &MyDevice::m_ViewPort);
	MyDevice::m_pContext->OMSetBlendState(m_pAlphaBlend.Get(), 0, -1);
}
void  MyCore::GamePostRender()
{
	//m_font.DrawText(m_Timer.m_csBuffer, { 0,0 });
	m_font.RenderSysInfo(m_Timer.m_csBuffer, D2D1_RECT_F{ 3, 700, 700, 720 }, D2D1_COLOR_F{ 0, 255, 0, 1 });
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
	// �׷��� ó���� ���� �ʱ�ȭ �۾�
	if (MyDevice::CreateDevice(m_hWnd))
	{
		I_Tex.Set(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext);
		I_Shader.Set(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext);
		SetAlphaBlendState();

		I_Sound.Set(nullptr, nullptr);
		I_Sprite.Load(L"../../resource/SpriteInfo.txt");

		m_font.Init();
		// 3D ����۸� �� �����ؾ� �Ѵ�.
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