#include "MyCore.h"
void MyCore::Init(){}
void MyCore::Frame() {}
void MyCore::Render() {}
void MyCore::Release() {}

void   MyCore::GamePreFrame()
{ 
	m_Timer.Frame();
	if (m_isActive)
	{
		m_Input.Frame(m_hWnd);
	}
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
	m_pContext->ClearRenderTargetView(m_pRTV, clearColor);

	m_pContext->OMSetRenderTargets(1, &m_pRTV, nullptr);
	m_pContext->RSSetViewports(1, &m_ViewPort);
}
void  MyCore::GamePostRender()
{
	m_font.DrawText(m_Timer.m_csBuffer, { 0,0 });
	m_pSwapChain->Present(0, 0);
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
	m_Input.DebugMousePos();
	m_Input.KeyTest();*/
}
void   MyCore::GameInit()
{
	// �׷��� ó���� ���� �ʱ�ȭ �۾�
	if (MyDevice::CreateDevice(m_hWnd))
	{
		m_font.Init();
		// 3D ����۸� �� �����ؾ� �Ѵ�.
		IDXGISurface* dxgiSurface = nullptr;
		m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
			(void**)&dxgiSurface);
		m_font.ResetDevice(dxgiSurface);
		dxgiSurface->Release();
	}
	Init();
}
void   MyCore::GameRun()
{
	GameInit();
	while(m_bGameRun)
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
	m_font.Release();
	DeleteDevice();
}