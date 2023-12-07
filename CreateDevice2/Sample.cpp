#include "Sample.h"
bool    Sample::Init()
{     
    // v0       v1
    //
    // v3       v2
    //m_VertexList.emplace_back(0.0f, 0.0f);      // 0
    //m_VertexList.emplace_back(800.0f, 0.0f);    // 1
    //m_VertexList.emplace_back(800.0f, 600.0f);  // 2
    //m_VertexList.emplace_back(0.0f, 600.0f);    // 3

    m_VertexList.emplace_back(0.0f, 1.0f);      // 0
    m_VertexList.emplace_back(1.0f, 1.0f);      // 1
    m_VertexList.emplace_back(1.0f, 0.0f);      // 2
    m_VertexList.emplace_back(0.0f, 0.0f);      // 3

    m_IndexList.push_back(0);
    m_IndexList.push_back(1);
    m_IndexList.push_back(2);

    m_IndexList.push_back(2);
    m_IndexList.push_back(3);
    m_IndexList.push_back(0);

    HRESULT hr1, hr2;
    m_pVertexBuffer = CreateBuffer(m_VertexList.size() * sizeof(TVertex), D3D11_BIND_VERTEX_BUFFER, (void**)&m_VertexList.at(0), &hr1);
    m_pIndexBuffer = CreateBuffer(m_IndexList.size() * sizeof(DWORD), D3D11_BIND_INDEX_BUFFER, (void**)&m_IndexList.at(0), &hr2);
    if (FAILED(hr1) || FAILED(hr2))
        return false;

    if (!CreateVertexShader() || !CreatePixelShader())
        return false;

    if (!CreateInputLayout())
        return false;

    return true;
}

bool    Sample::Render() 
{   
    m_pd3dContext->VSSetShader(m_pVertexShader, NULL, 0);
    m_pd3dContext->PSSetShader(m_pPixelShader, NULL, 0);
    m_pd3dContext->IASetInputLayout(m_pVertexlayout);
    m_pd3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    UINT pStrides = sizeof(TVertex);
    UINT pOffsets = 0;
    m_pd3dContext->IASetVertexBuffers(
        0,
        1,
        &m_pVertexBuffer,
        &pStrides,
        &pOffsets);
    m_pd3dContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3dContext->DrawIndexed(m_IndexList.size(), 0, 0);

    return true;
}

bool    Sample::Release() 
{   
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pIndexBuffer) m_pIndexBuffer->Release();
    if (m_pVertexShaderCode) m_pVertexShaderCode->Release();
    if (m_pPixelShaderCode) m_pPixelShaderCode->Release();
    if (m_pVertexShader) m_pVertexShader->Release();
    if (m_pPixelShader) m_pPixelShader->Release();
    if (m_pVertexlayout) m_pVertexlayout->Release();

    return true;
}

//HINSTANCE : 운영체제가 관리하는 윈도우 프로세스ID
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

ID3D11Buffer* Sample::CreateBuffer(UINT ByteWidth, UINT BindFlags, void** pSysMem, HRESULT* hr)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth  = ByteWidth; // 메모리 할당 크기
    bd.Usage      = D3D11_USAGE_DEFAULT; // 버퍼의 저장소 및 접근권한 설정
    bd.BindFlags  = BindFlags; // 버퍼의 용도

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = pSysMem; // 항상 연속된 메모리를 가지는 데이터 구조만 들어갈 수 있다 (맨앞의 데이터의 주소를 넣는다)

    ID3D11Buffer* vertexBuffer;
    *hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &vertexBuffer); // 항상 무언가를 생성할때는 device 의 메소드로 간다

    return vertexBuffer;
}

// 정점쉐이더 만들기
bool Sample::CreateVertexShader()
{
    HRESULT hr;

    ID3DBlob* ppErrorMsgs = nullptr; // 컴파일러의 에러 코드
    // 쉐이더 파일을 읽어서 바이트 코드로 컴파일한다
    hr = D3DCompileFromFile(L"Shader.txt", // 이 파일을 로딩해서
        nullptr,
        nullptr,
        "VS", // 이 함수를 컴파일한다. (엔트리포인트)
        "vs_5_0", // 이 컴파일러로 컴파일 한다.
        0,
        0,
        &m_pVertexShaderCode,
        &ppErrorMsgs);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)ppErrorMsgs->GetBufferPointer(), "Error!", MB_OK);
        if (ppErrorMsgs) ppErrorMsgs->Release();
        return false;
    }
    if (ppErrorMsgs) ppErrorMsgs->Release();

    hr = m_pd3dDevice->CreateVertexShader(
        m_pVertexShaderCode->GetBufferPointer(),
        m_pVertexShaderCode->GetBufferSize(),
        nullptr,
        &m_pVertexShader);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

// 픽셀쉐이더 만들기
bool Sample::CreatePixelShader()
{
    HRESULT hr;

    ID3DBlob* ppErrorMsgs = nullptr;
    hr = D3DCompileFromFile(L"Shader.txt",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        0,
        0,
        &m_pPixelShaderCode,
        &ppErrorMsgs);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)ppErrorMsgs->GetBufferPointer(), "Error!", MB_OK);
        if (ppErrorMsgs) ppErrorMsgs->Release();
        return false;
    }
    if (ppErrorMsgs) ppErrorMsgs->Release();

    hr = m_pd3dDevice->CreatePixelShader(
        m_pPixelShaderCode->GetBufferPointer(),
        m_pPixelShaderCode->GetBufferSize(),
        nullptr,
        &m_pPixelShader);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool Sample::CreateInputLayout()
{
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    /*LPCSTR SemanticName;
    UINT SemanticIndex;
    DXGI_FORMAT Format;
    UINT InputSlot;
    UINT AlignedByteOffset;
    D3D11_INPUT_CLASSIFICATION InputSlotClass;
    UINT InstanceDataStepRate;*/

    UINT iNumInput;
    HRESULT hr = m_pd3dDevice->CreateInputLayout(
        layout,
        1,
        m_pVertexShaderCode->GetBufferPointer(),
        m_pVertexShaderCode->GetBufferSize(),
        &m_pVertexlayout);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

