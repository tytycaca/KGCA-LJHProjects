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
	// ����Ʈ ���۸� �����
	g_pContext->ClearRenderTargetView(g_pRTV, clearColor);
}

void MyCore::GamePostRender()
{
	// ����ۿ� ����Ʈ ���۸� �����Ѵ� (ȭ�� ǥ��)
	g_pSwapChain->Present(0, 0);
}

void MyCore::GameRender()
{
	GamePreRender();
	Render(); // ���ӷ�����, ����, ������Ʈ, ĳ����, UI, ����Ʈ...
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