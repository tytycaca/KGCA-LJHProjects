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
	// ����Ʈ ���۸� �����
	g_pContext->ClearRenderTargetView(g_pRTV, clearColor);
}

void MyCore::GamePostRender()
{
	// fps, time ǥ��
	m_Font.DrawTextW(m_Timer.m_csBuffer, { 0, 0 });
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
	// �׷��� ó���� ���� �ʱ�ȭ �۾�
	if (CreateDevice(m_hWnd))
	{
		m_Font.Init();
		// 3D ����۸� �� �����ؾ� �Ѵ�.
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
	// �ʱ�ȭ
	GameInit();

	// ���� ���� ����
	while (1)
	{
		if (MyWindow::WindowRun() == false)
		{
			break;
		}
		GameFrame();
		GameRender();
	}

	// ������
	GameRelease();
}

void MyCore::GameRelease()
{
	Release();
	m_Font.Release();
	DeleteDevice();
}