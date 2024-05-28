#include "MyCore.h"

void MyCore::Init()
{

}
void MyCore::Frame()
{

}
void MyCore::Render()
{

}
void MyCore::Release()
{

}

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
	
}

void MyCore::GamePostFrame()
{

}

void MyCore::GamePreRender()
{
	float clearColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	// 프론트 버퍼를 지운다
	g_pContext->ClearRenderTargetView(g_pRTV, clearColor);
}

void MyCore::GamePostRender()
{
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
	Init();
}

void MyCore::GameRun()
{
	GamePreFrame();
	GameFrame();
	GamePostFrame();
	GameRender();
}

void MyCore::GameRelease()
{
	Release();
	DeleteDevice();
}