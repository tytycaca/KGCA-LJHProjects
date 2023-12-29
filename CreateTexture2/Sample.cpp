#include "Sample.h"
bool Sample::CreateSampleState()
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
bool Sample::CreatePixelShader()
{
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    HRESULT hr = m_pd3dDevice->CreateSamplerState(&sd, &m_pDefaultSS);

    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    hr = m_pd3dDevice->CreateSamplerState(&sd, &m_pDefaultSSPoint);

    ID3DBlob* pBlobByteCode;
    ID3DBlob* ppErrorMsgs = nullptr;
    hr = D3DCompileFromFile(
        L"DefaultShaderVSPS.txt",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        0,
        0,
        &pBlobByteCode,
        &ppErrorMsgs);
    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)ppErrorMsgs->GetBufferPointer(), "Error", MB_OK);
        if (ppErrorMsgs) ppErrorMsgs->Release();
        return false;
    }
    if (ppErrorMsgs) ppErrorMsgs->Release();

    //m_pd3dDevice->CreatePixelShader();

    hr = m_pd3dDevice->CreatePixelShader(
        pBlobByteCode->GetBufferPointer(),
        pBlobByteCode->GetBufferSize(),
        nullptr,
        &m_pPixelShaderAlphaTest);

    if (pBlobByteCode)pBlobByteCode->Release();
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}
bool Sample::AlphaBlendState()
{
    D3D11_BLEND_DESC bsd;
    ZeroMemory(&bsd, sizeof(bsd));
    //bsd.AlphaToCoverageEnable = TRUE;
    bsd.RenderTarget[0].BlendEnable = TRUE;
 
    // rgb  
 //FINALCOLOR = DEST COLOR* (1-SRCALPHA) + SRC COLOR * SRC ALPAH
    bsd.RenderTarget[0].SrcBlend= D3D11_BLEND_SRC_ALPHA;
    bsd.RenderTarget[0].DestBlend= D3D11_BLEND_INV_SRC_ALPHA;
    bsd.RenderTarget[0].BlendOp= D3D11_BLEND_OP_ADD;

    // A
    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha= D3D11_BLEND_ZERO;
    bsd.RenderTarget[0].BlendOpAlpha= D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].RenderTargetWriteMask= D3D11_COLOR_WRITE_ENABLE_ALL;


    HRESULT hr = m_pd3dDevice->CreateBlendState(
        &bsd,
        &m_pAlphaBlendEnable);

    bsd.RenderTarget[0].BlendEnable = FALSE;
    hr = m_pd3dDevice->CreateBlendState(
        &bsd,
        &m_pAlphaBlendDisable);

    m_pd3dContext->OMSetBlendState(m_pAlphaBlendEnable, 0, -1);
    return true;
}

bool    Sample::Init()
{     
    AlphaBlendState();
    CreateSampleState();
    CreatePixelShader();

    m_bk.m_pd3dDevice = m_pd3dDevice;
    m_bk.m_pd3dContext = m_pd3dContext;
    m_bk.m_rtClient = m_rtClient;
    // v0       v1
//
// v3       v2
    m_bk.m_VertexList.emplace_back(TVector3(0.0f, 0.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 0.0f));      // 0
    m_bk.m_VertexList.emplace_back(TVector3(m_rtClient.right, 0.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 0.0f));    // 1
    m_bk.m_VertexList.emplace_back(TVector3(m_rtClient.right, m_rtClient.bottom, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 1.0f));  // 2
    m_bk.m_VertexList.emplace_back(TVector3(0.0f, m_rtClient.bottom, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 1.0f));    // 3

    m_bk.Init();
    m_bk.Load(L"../../data/ball4.dds");
   // v0       v1
//
// v3       v2
    m_SkillLayout.m_pd3dDevice = m_pd3dDevice;
    m_SkillLayout.m_pd3dContext = m_pd3dContext;
    m_SkillLayout.m_rtClient = m_rtClient;
 
    m_SkillLayout.m_VertexList.emplace_back(TVector3(18.0f, 477.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 0.0f));      // 0
    m_SkillLayout.m_VertexList.emplace_back(TVector3(460, 477.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 0.0f));    // 1
    m_SkillLayout.m_VertexList.emplace_back(TVector3(460, 600, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 1.0f));  // 2
    m_SkillLayout.m_VertexList.emplace_back(TVector3(18.0f, 600, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 1.0f));    // 3

    m_SkillLayout.Init();
    m_SkillLayout.Load(L"../../data/skill.png");
    // v0       v1
//
// v3       v2
    m_Skill2.m_pd3dDevice = m_pd3dDevice;
    m_Skill2.m_pd3dContext = m_pd3dContext;
    m_Skill2.m_rtClient = m_rtClient;

    m_Skill2.m_VertexList.emplace_back(TVector3(115.0f, 487.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 0.0f));      // 0
    m_Skill2.m_VertexList.emplace_back(TVector3(178.0f, 487.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 0.0f));    // 1
    m_Skill2.m_VertexList.emplace_back(TVector3(178.0f, 590, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 1.0f));  // 2
    m_Skill2.m_VertexList.emplace_back(TVector3(115.0f, 590, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 1.0f));    // 3

    m_Skill2.Init();
    if (!m_Skill2.Load(L"../../data/s2.png"))
    {
        return false;
    }
    m_Skill2.LoadTextureChange(L"../../data/s1.png");


    m_Number.m_pd3dDevice = m_pd3dDevice;
    m_Number.m_pd3dContext = m_pd3dContext;
    m_Number.m_rtClient = m_rtClient;

    m_Number.m_VertexList.emplace_back(TVector3(0, 0.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 0.0f));      // 0
    m_Number.m_VertexList.emplace_back(TVector3(52.0f, 0.0f, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 0.0f));    // 1
    m_Number.m_VertexList.emplace_back(TVector3(52.0f, 68, 0.5f), TVector4(1, 1, 1, 1), TVector2(1.0f, 1.0f));  // 2
    m_Number.m_VertexList.emplace_back(TVector3(0.0f, 68, 0.5f), TVector4(1, 1, 1, 1), TVector2(0.0f, 1.0f));    // 3

    m_Number.Init();
    if (!m_Number.Load(L"../../data/0.png"))
    {
        return false;
    }    
    return true;
}
bool    Sample::Render() 
{   
    m_pd3dContext->PSSetSamplers(0, 1, &m_pDefaultSS);
    m_pd3dContext->OMSetBlendState(m_pAlphaBlendEnable, 0, -1);

    m_bk.PreRender();
    m_bk.PostRender();

    m_SkillLayout.Render();

    if(g_bChange)
        m_Skill2.Render();
    else
        m_Skill2.RenderChange();

  
    m_pd3dContext->PSSetShaderResources(0, 1, &m_Number.m_pTextureSRVArray[g_iChangeAnimation]);
    UINT pStrides = sizeof(TVertex);
     UINT pOffsets = 0;
     m_pd3dContext->IASetVertexBuffers(
         0,
         1,
         &m_Number.m_pVertexBuffer,
         &pStrides,
         &pOffsets);
     m_pd3dContext->DrawIndexed(m_Number.m_IndexList.size(), 0, 0);
     return true;
}
bool    Sample::Release() 
{  
    if (m_pDefaultSS)m_pDefaultSS->Release();
    if (m_pDefaultSSPoint)m_pDefaultSSPoint->Release();
    if (m_pAlphaBlendEnable)m_pAlphaBlendEnable->Release();
    if (m_pAlphaBlendDisable)m_pAlphaBlendDisable->Release();
    if (m_pPixelShaderAlphaTest)m_pPixelShaderAlphaTest->Release();
    m_bk.Release();
    m_SkillLayout.Release();
    m_Skill2.Release();
    m_Number.Release();
    return true;
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



