#include "Sample.h"

bool Sample::Init()
{
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
    UINT Flags = 0;
    D3D_FEATURE_LEVEL  pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    DXGI_SWAP_CHAIN_DESC sd;
    //DXGI_MODE_DESC BufferDesc;
    sd.BufferDesc.Width = 800;
    sd.BufferDesc.Height = 600;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    //DXGI_SAMPLE_DESC SampleDesc;
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

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    if (pBackBuffer) pBackBuffer->Release();

    m_pd3dContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    return true;
}

bool Sample::Render()
{
    float clearColor[] = { 0,1,0,1 };
    m_pd3dContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    m_pSwapChain->Present(0, 0);
    return true;
}

bool Sample::Release()
{
    if (m_pd3dDevice != nullptr) m_pd3dDevice->Release();
    if (m_pd3dContext) m_pd3dContext->Release();
    if (m_pRenderTargetView) m_pRenderTargetView->Release();
    if (m_pSwapChain) m_pSwapChain->Release();
    m_pd3dDevice = nullptr;
    m_pd3dContext = nullptr;
    m_pRenderTargetView = nullptr;
    m_pSwapChain = nullptr;
    return true;
}

bool Sample::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));

    bd.ByteWidth = m_vertexList.size() * sizeof(Vertex);
    bd.Usage     = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    sd.pSysMem = &m_vertexList.at(0);

    HRESULT hr;

    hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_vertexBuffer);
    if (FAILED(hr)) return false;

    return false;
}

//HINSTANCE : �ü���� �����ϴ� ������ ���μ���ID
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Sample win;
    win.SetWindow(hInstance, nCmdShow);
    win.Run();
    return 0;
}

