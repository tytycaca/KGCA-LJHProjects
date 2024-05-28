#ifndef UNICODE
#define UNICODE
#endif
#include "MyWindow.h"
#include <d3d11.h> // DirectX ���
// 1�� ���: �Ӽ� -> ��Ŀ -> �Է� -> �߰����Ӽ� -> d3d11.lib �߰�
// 2�� ���: #pragma comment ( lib, "d3d11.lib" )
// �������� �� �س��� �������.
#pragma comment (lib, "d3d11.lib")

class MyDevice : public MyWindow
{
public:
	// �������̽� ȹ�� (�Ҵ�, ����)
	ID3D11Device*			g_pd3dDevice = nullptr;
	ID3D11DeviceContext*	g_pContext = nullptr;
	IDXGISwapChain*			g_pSwapChain = nullptr;
	ID3D11RenderTargetView* g_pRTV = nullptr;	// ȭ���� ��� �Ѹ��� ����

	bool CreateDevice(HWND hWnd);
	void DeleteDevice();

	virtual void GameRun() override;
};

int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					PWSTR pCmdLine,
					int nCmdShow)
{
	MyDevice MyWin;

	MyWin.CreateRegisterClass(hInstance);
	if (MyWin.CreateWin(1024, 768))
	{
		// �׷��� ó���� ���� �ʱ�ȭ �۾�
		if (MyWin.CreateDevice(MyWin.m_hWnd))
		{
			MyWin.WindowRun();
		}
		
		// �׷��� ó���� ���� �Ҹ� �۾�
		MyWin.DeleteDevice();
	}

	return 0;
}

bool MyDevice::CreateDevice(HWND hWnd)
{
	CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC pSwapChainDesc;
	ZeroMemory(&pSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	pSwapChainDesc.BufferDesc.Width = 1024;
	pSwapChainDesc.BufferDesc.Height = 768;
	pSwapChainDesc.BufferDesc.RefreshRate;
	pSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	pSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	pSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	pSwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	pSwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	pSwapChainDesc.SampleDesc.Count = 1;
	pSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	pSwapChainDesc.BufferCount = 1;
	pSwapChainDesc.OutputWindow = hWnd;
	pSwapChainDesc.Windowed = true;

	// ID3D11Device, ID3D11DeviceContext, IDXGISwapChain �� 3������ �ϳ��� �Լ��� ȹ���� �� �ִ�.
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&pSwapChainDesc,
		&g_pSwapChain,
		&g_pd3dDevice,
		nullptr,
		&g_pContext);
	if (FAILED(hr))
	{
		return false;
	}
	if (g_pd3dDevice != nullptr && g_pSwapChain != nullptr)
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

		ID3D11Resource* pResource = pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc = nullptr;
		hr = g_pd3dDevice->CreateRenderTargetView(
			pResource,
			pDesc,
			&g_pRTV);
		if (FAILED(hr))
		{
			return false;
		}

		pBackBuffer->Release();
	}

	if(g_pContext != nullptr)
	{
		g_pContext->OMSetRenderTargets(1, &g_pRTV, nullptr);
	}
	return true;
}

void MyDevice::DeleteDevice()
{
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pSwapChain) g_pd3dDevice->Release();
	if (g_pSwapChain) g_pContext->Release();
	if (g_pSwapChain) g_pRTV->Release();
}

void MyDevice::GameRun()
{
	float clearColor[] = {0.0f, 1.0f, 0.0f, 1.0f};
	// ����Ʈ ���۸� �����
	g_pContext->ClearRenderTargetView(g_pRTV, clearColor);
	// ����ۿ� ����Ʈ ���۸� �����Ѵ�
	g_pSwapChain->Present(0, 0);
}
