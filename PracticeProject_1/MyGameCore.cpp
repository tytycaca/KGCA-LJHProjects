#include "MyGameCore.h"

bool MyGameCore::CreateSampleState()
{
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    HRESULT hr = m_pd3dDevice->CreateSamplerState(&sd, &m_pDefaultSS);
    if (FAILED(hr)) return false;

    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    hr = m_pd3dDevice->CreateSamplerState(&sd, &m_pDefaultSSPoint);
    return true;
}

bool MyGameCore::AlphaBlendState()
{
    D3D11_BLEND_DESC bsd;
    ZeroMemory(&bsd, sizeof(bsd));
    //bsd.AlphaToCoverageEnable = TRUE;
    bsd.RenderTarget[0].BlendEnable = TRUE;

    // rgb  
 //FINALCOLOR = DEST COLOR* (1-SRCALPHA) + SRC COLOR * SRC ALPAH
    bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    // A
    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


    HRESULT hr = m_pd3dDevice->CreateBlendState(
        &bsd,
        &m_pAlphaBlendEnable);

    bsd.RenderTarget[0].BlendEnable = FALSE;
    hr = m_pd3dDevice->CreateBlendState(
        &bsd,
        &m_pAlphaBlendDisable);

    return true;
}

bool MyGameCore::DualSourceColorBlending()
{
    D3D11_BLEND_DESC bsd;
    ZeroMemory(&bsd, sizeof(bsd));
    //bsd.AlphaToCoverageEnable = TRUE;
    bsd.RenderTarget[0].BlendEnable = TRUE;
    //bsd.IndependentBlendEnable = TRUE;

    // rgb  
 //FINALCOLOR = DEST COLOR* (1-SRCALPHA) + SRC COLOR * SRC ALPAH
    bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;         // SV_TARGET0
    bsd.RenderTarget[0].DestBlend = D3D11_BLEND_SRC1_COLOR; // SV_TARGET1
    bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    // A
    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


    HRESULT hr = m_pd3dDevice->CreateBlendState(
        &bsd,
        &m_pDualSourceColorBlending);

    return true;
}

bool MyGameCore::GameInit()
{
	CreateDevice();

    AlphaBlendState();
    DualSourceColorBlending();
    CreateSampleState();

	m_MyTimer.Init();
    MyInput::Get().Init();
    MyTextureMgr::Get().Set(m_pd3dDevice, m_pd3dContext);

    // MyDxWrite 초기화
	IDXGISurface* dxgiSurface;
	HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);
	if (SUCCEEDED(hr))
	{
		MyDxWrite::Get().Init(dxgiSurface);
		if (dxgiSurface)dxgiSurface->Release();
	}

    m_BackgroundPlane = std::make_shared<MyPlaneShape>();

    m_BackgroundPlane->m_pd3dDevice = m_pd3dDevice;
    m_BackgroundPlane->m_pd3dContext = m_pd3dContext;
    m_BackgroundPlane->m_rtClientWindow = m_rtClientWindow;

    m_BackgroundPlane->m_VertexList.emplace_back(MyVector3(0, 0.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_BackgroundPlane->m_VertexList.emplace_back(MyVector3(1600.0f, 0.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_BackgroundPlane->m_VertexList.emplace_back(MyVector3(1600.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_BackgroundPlane->m_VertexList.emplace_back(MyVector3(0.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_BackgroundPlane->Create(L"BackgroundPlane", L"../../data/resources/bg.png"))
    {
        return false;
    }

    m_BoxPlane = std::make_shared<MyPlaneShape>();

    m_BoxPlane->m_pd3dDevice = m_pd3dDevice;
    m_BoxPlane->m_pd3dContext = m_pd3dContext;
    m_BoxPlane->m_rtClientWindow = m_rtClientWindow;

    m_BoxPlane->m_VertexList.emplace_back(MyVector3(550.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_BoxPlane->m_VertexList.emplace_back(MyVector3(1050.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_BoxPlane->m_VertexList.emplace_back(MyVector3(1050.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_BoxPlane->m_VertexList.emplace_back(MyVector3(550.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_BoxPlane->Create(L"BoxPlane", L"../../data/resources/orangeGradation.png"))
    {
        return false;
    }

    m_LeftBarPlane = std::make_shared<MyPlaneShape>();

    m_LeftBarPlane->m_pd3dDevice = m_pd3dDevice;
    m_LeftBarPlane->m_pd3dContext = m_pd3dContext;
    m_LeftBarPlane->m_rtClientWindow = m_rtClientWindow;

    m_LeftBarPlane->m_VertexList.emplace_back(MyVector3(540.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_LeftBarPlane->m_VertexList.emplace_back(MyVector3(550.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_LeftBarPlane->m_VertexList.emplace_back(MyVector3(550.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_LeftBarPlane->m_VertexList.emplace_back(MyVector3(540.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_LeftBarPlane->Create(L"LeftBarPlane", L"../../data/resources/skyblue.png"))
    {
        return false;
    }

    m_RightBarPlane = std::make_shared<MyPlaneShape>();

    m_RightBarPlane->m_pd3dDevice = m_pd3dDevice;
    m_RightBarPlane->m_pd3dContext = m_pd3dContext;
    m_RightBarPlane->m_rtClientWindow = m_rtClientWindow;

    m_RightBarPlane->m_VertexList.emplace_back(MyVector3(1050.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_RightBarPlane->m_VertexList.emplace_back(MyVector3(1060.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_RightBarPlane->m_VertexList.emplace_back(MyVector3(1060.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_RightBarPlane->m_VertexList.emplace_back(MyVector3(1050.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_RightBarPlane->Create(L"RightBarPlane", L"../../data/resources/skyblue.png"))
    {
        return false;
    }

    m_BottomBarPlane = std::make_shared<MyPlaneShape>();

    m_BottomBarPlane->m_pd3dDevice = m_pd3dDevice;
    m_BottomBarPlane->m_pd3dContext = m_pd3dContext;
    m_BottomBarPlane->m_rtClientWindow = m_rtClientWindow;

    m_BottomBarPlane->m_VertexList.emplace_back(MyVector3(551.0f, 890.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_BottomBarPlane->m_VertexList.emplace_back(MyVector3(1049.0f, 890.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_BottomBarPlane->m_VertexList.emplace_back(MyVector3(1049.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_BottomBarPlane->m_VertexList.emplace_back(MyVector3(551.0f, 900.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_BottomBarPlane->Create(L"BottomBarPlane", L"../../data/resources/skyblue.png"))
    {
        return false;
    }

    m_TitlePlane = std::make_shared<MyPlaneShape>();

    m_TitlePlane->m_pd3dDevice = m_pd3dDevice;
    m_TitlePlane->m_pd3dContext = m_pd3dContext;
    m_TitlePlane->m_rtClientWindow = m_rtClientWindow;

    m_TitlePlane->m_VertexList.emplace_back(MyVector3(75.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_TitlePlane->m_VertexList.emplace_back(MyVector3(465.0f, 200.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_TitlePlane->m_VertexList.emplace_back(MyVector3(465.0f, 425.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_TitlePlane->m_VertexList.emplace_back(MyVector3(75.0f, 425.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_TitlePlane->Create(L"TitlePlane", L"../../data/resources/title.png"))
    {
        return false;
    }

    m_FruitLevelPlane = std::make_shared<MyPlaneShape>();

    m_FruitLevelPlane->m_pd3dDevice = m_pd3dDevice;
    m_FruitLevelPlane->m_pd3dContext = m_pd3dContext;
    m_FruitLevelPlane->m_rtClientWindow = m_rtClientWindow;

    m_FruitLevelPlane->m_VertexList.emplace_back(MyVector3(75.0f, 400.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 0.0f));      // 0
    m_FruitLevelPlane->m_VertexList.emplace_back(MyVector3(465.0f, 400.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 0.0f));    // 1
    m_FruitLevelPlane->m_VertexList.emplace_back(MyVector3(465.0f, 790.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(1.0f, 1.0f));  // 2
    m_FruitLevelPlane->m_VertexList.emplace_back(MyVector3(75.0f, 790.0f, 0.5f), MyVector4(1, 1, 1, 1), MyVector2(0.0f, 1.0f));    // 3
    if (!m_FruitLevelPlane->Create(L"FruitLevelPlane", L"../../data/resources/fruitLevel.png"))
    {
        return false;
    }
	
	Init();

	return true;
}

bool MyGameCore::GameFrame()
{
	m_MyTimer.Frame();
    MyInput::Get().Frame();
	MyDxWrite::Get().Frame();

	Frame();

	return true;
}

bool MyGameCore::GameRender()
{
    float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_pd3dContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);

    m_pd3dContext->PSSetSamplers(0, 1, &m_pDefaultSS);
    m_pd3dContext->OMSetBlendState(m_pAlphaBlendEnable, 0, -1);

    m_pd3dContext->UpdateSubresource(m_BackgroundPlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_BackgroundPlane->m_VertexList.at(0),
        0,
        0);
    m_BackgroundPlane->Render();

    m_pd3dContext->UpdateSubresource(m_BoxPlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_BoxPlane->m_VertexList.at(0),
        0,
        0);
    m_BoxPlane->Render();

    m_pd3dContext->UpdateSubresource(m_LeftBarPlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_LeftBarPlane->m_VertexList.at(0),
        0,
        0);
    m_LeftBarPlane->Render();

    m_pd3dContext->UpdateSubresource(m_RightBarPlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_RightBarPlane->m_VertexList.at(0),
        0,
        0);
    m_RightBarPlane->Render();

    m_pd3dContext->UpdateSubresource(m_BottomBarPlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_BottomBarPlane->m_VertexList.at(0),
        0,
        0);
    m_BottomBarPlane->Render();

    m_pd3dContext->UpdateSubresource(m_TitlePlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_TitlePlane->m_VertexList.at(0),
        0,
        0);
    m_TitlePlane->Render();

    m_pd3dContext->UpdateSubresource(m_FruitLevelPlane->m_pVertexBuffer,
        0,
        nullptr,
        &m_FruitLevelPlane->m_VertexList.at(0),
        0,
        0);
    m_FruitLevelPlane->Render();
    
	Render();

	// m_MyTimer.Render(); // 출력 테스트용
    MyInput::Get().Render();
	// MyDxWrite::Get().Render(); // 출력 테스트용

    // 시스템 정보 출력
    MyDxWrite::Get().DrawGothic20(720, 0, L" 게임 경과 시간: " + std::to_wstring((UINT)m_MyTimer.m_fGameTimer));
    MyDxWrite::Get().DrawGothic15(1540, 0, m_MyTimer.m_msgFPS);

    m_pSwapChain->Present(0, 0);

	return true;
}

bool MyGameCore::GameRelease()
{
	m_MyTimer.Release();
	MyDxWrite::Get().Release();

    if (m_pDefaultSS)m_pDefaultSS->Release();
    if (m_pDefaultSSPoint)m_pDefaultSSPoint->Release();
    if (m_pAlphaBlendEnable)m_pAlphaBlendEnable->Release();
    if (m_pAlphaBlendDisable)m_pAlphaBlendDisable->Release();
    if (m_pDualSourceColorBlending)m_pDualSourceColorBlending->Release();

	Release();

	DeleteDevice();

	return true;
}
