#include "MyDevice.h"


bool MyDevice::CreateDevice(HWND hWnd)
{
	// DWRITE ������ �ʿ���.
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC pSwapChainDesc;
	ZeroMemory(&pSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	pSwapChainDesc.BufferDesc.Width = m_xClientSize;
	pSwapChainDesc.BufferDesc.Height = m_yClientSize;
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
		Flags,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&pSwapChainDesc,
		&m_pSwapChain,
		&m_pd3dDevice,
		nullptr,
		&m_pContext);
	if (FAILED(hr))
	{
		return false;
	}

	if (m_pd3dDevice != nullptr && m_pSwapChain != nullptr)
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

		ID3D11Resource* pResource = pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc = nullptr;
		hr = m_pd3dDevice->CreateRenderTargetView(
			pResource,
			pDesc,
			&m_pRTV);
		if (FAILED(hr))
		{
			return false;
		}

		pBackBuffer->Release();
	}

	SetViewport();

	/*if (m_pContext != nullptr)
	{
		m_pContext->OMSetRenderTargets(1, &m_pRTV, nullptr);
	}*/
	return true;
}

void MyDevice::DeleteDevice()
{
	if (m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
	if (m_pSwapChain)
	{
		m_pd3dDevice->Release();
		m_pd3dDevice = nullptr;
	}
	if (m_pSwapChain)
	{
		m_pContext->Release();
		m_pContext = nullptr;
	}
	if (m_pSwapChain)
	{
		m_pRTV->Release();
		m_pRTV = nullptr;
	}
}

void MyDevice::SetViewport()
{
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = m_xClientSize;
	m_ViewPort.Height = m_yClientSize;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;
	m_pContext->RSSetViewports(1, &m_ViewPort);
}
