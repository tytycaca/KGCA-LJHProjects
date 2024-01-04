#include "MyDevice.h"

bool MyDevice::CreateDevice()
{
    // 1. 드라이버 타입, 플래그, D3D 버전 설정
    // 2. 스왑체인 디스크립션 객체 생성 및 내용 채우기
    // 3. 디바이스와 스왑체인 생성 (위에서 설정했던 드라이버 타입, 플래그, 스왑체인 디스크립션 객체 사용)
    // 4. 2d 텍스쳐 백버퍼 만들고 스왑체인 멤버변수의 GetBuffer() 사용하여 백버퍼 할당
    // 5. 디바이스 멤버변수의 CreateRenderTargetView() 와 백버퍼를 사용하여 렌더타겟뷰 할당
    // 6. 사용 후 쓸모없어진 백버퍼 릴리즈
    // 7. 렌더링 파이프라인 OM 단계에 렌더타겟뷰 묶기 (OMSetRenderTargets())
    // 8. 뷰포트 객체 생성 후 내용 채우기
    // 9. 렌더링 파이프라인 RS 단계에 뷰포트 묶기

    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;   // 하드웨어 가속 설정
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;           // Direct2D 와 Direct3D 리소스의 상호운영을 가능하게 함

#ifdef _DEBUG   // 디버그시에만 사용할 코드
    Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL pFeatureLevels[] =    // Direct3D 버전 설정
    {
        D3D_FEATURE_LEVEL_11_0,
    };

    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = 1600;
    sd.BufferDesc.Height = 900;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.RefreshRate.Numerator = 100;   // 주사율 100 hz
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
