#include "MyCore.h"

void MyCore::Init() {}
void MyCore::Frame() {}
void MyCore::Render() {}
void MyCore::Release() {}

void MyCore::GamePreFrame()
{
	m_Timer.Frame();
	if (m_isActive)
	{
		m_Input.Frame(m_hWnd);
	}
}

void MyCore::GameFrame()
{
	GamePreFrame();
	Frame();
	GamePostFrame();
}

void MyCore::GamePostFrame()
{

}

void MyCore::GamePreRender()
{
	float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 프론트 버퍼를 지운다
	g_pContext->ClearRenderTargetView(g_pRTV, clearColor);
}

void MyCore::GamePostRender()
{
	// fps, time 표시
	m_Font.DrawTextW(m_Timer.m_csBuffer, { 0, 0 });
	// 백버퍼와 프론트 버퍼를 스왑한다 (화면 표시)
	g_pSwapChain->Present(0, 0);
}

void MyCore::GameRender()
{
	GamePreRender();
	Render(); // 게임렌더링, 지형, 오브젝트, 캐릭터, UI, 이펙트...
	GamePostRender();
	DebugRender();
}

void MyCore::DebugRender()
{
	/*m_Timer.DebugTimer();
	m_Input.DebugMousePos();
	m_Input.KeyTest();*/
}

void MyCore::GameInit()
{
	// 그래픽 처리를 위한 초기화 작업
	if (CreateDevice(m_hWnd))
	{
		m_Font.Init();
		// 3D 백버퍼를 얻어서 전달해야 한다.
		IDXGISurface* dxgiSurface = nullptr;
		g_pSwapChain->GetBuffer(
			0,
			__uuidof(dxgiSurface),
			(void**)&dxgiSurface);
		m_Font.ResetDevice(dxgiSurface);
		dxgiSurface->Release();
	}
	Init();
}

void MyCore::GameRun()
{
	// 초기화
	GameInit();

	// 게임 메인 루프
	while (1)
	{
		if (MyWindow::WindowRun() == false)
		{
			break;
		}
		GameFrame();
		GameRender();
	}

	// 릴리즈
	GameRelease();
}

void MyCore::GameRelease()
{
	Release();
	m_Font.Release();
	DeleteDevice();
}