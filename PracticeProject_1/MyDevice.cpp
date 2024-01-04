#include "MyDevice.h"

bool MyDevice::CreateDevice()
{
    // 1. ����̹� Ÿ��, �÷���, D3D ���� ����
    // 2. ����ü�� ��ũ���� ��ü ���� �� ���� ä���
    // 3. ����̽��� ����ü�� ���� (������ �����ߴ� ����̹� Ÿ��, �÷���, ����ü�� ��ũ���� ��ü ���)
    // 4. 2d �ؽ��� ����� ����� ����ü�� ��������� GetBuffer() ����Ͽ� ����� �Ҵ�
    // 5. ����̽� ��������� CreateRenderTargetView() �� ����۸� ����Ͽ� ����Ÿ�ٺ� �Ҵ�
    // 6. ��� �� ��������� ����� ������
    // 7. ������ ���������� OM �ܰ迡 ����Ÿ�ٺ� ���� (OMSetRenderTargets())
    // 8. ����Ʈ ��ü ���� �� ���� ä���
    // 9. ������ ���������� RS �ܰ迡 ����Ʈ ����

    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;   // �ϵ���� ���� ����
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;           // Direct2D �� Direct3D ���ҽ��� ��ȣ��� �����ϰ� ��

#ifdef _DEBUG   // ����׽ÿ��� ����� �ڵ�
    Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL pFeatureLevels[] =    // Direct3D ���� ����
    {
        D3D_FEATURE_LEVEL_11_0,
    };

    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = 1600;
    sd.BufferDesc.Height = 900;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.RefreshRate.Numerator = 100;   // �ֻ��� 100 hz
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = m_hWnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        DriverType,
        nullptr,
        Flags,
        pFeatureLevels,
        1,
        D3D11_SDK_VERSION,
        &sd,
        &m_pSwapChain,
        &m_pd3dDevice,
        nullptr,
        &m_pd3dContext);
    if (FAILED(hr))
    {
        return false;
    }

    ID3D11Buffer* pBackBuffer = nullptr;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    if (FAILED(hr))
    {
        return false;
    }

    if (pBackBuffer) pBackBuffer->Release();

    m_pd3dContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = sd.BufferDesc.Width;
    vp.Height = sd.BufferDesc.Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    m_pd3dContext->RSSetViewports(1, &vp);

    return true;
}

bool MyDevice::DeleteDevice()
{
    if (m_pd3dDevice) m_pd3dDevice->Release();
    if (m_pd3dContext) m_pd3dContext->Release();
    if (m_pRenderTargetView) m_pRenderTargetView->Release();
    if (m_pSwapChain) m_pSwapChain->Release();
    m_pd3dDevice = nullptr;
    m_pd3dContext = nullptr;
    m_pRenderTargetView = nullptr;
    m_pSwapChain = nullptr;

    return true;
}
