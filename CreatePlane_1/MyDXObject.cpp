#include "MyDXObject.h"

MyDXObject& MyDXObject::Move(float dx, float dy)
{
    m_vList[0].p.X = m_vList[0].p.X + dx;
    m_vList[0].p.Y = m_vList[0].p.Y + dy;
    m_vList[1].p.X = m_vList[1].p.X + dx;
    m_vList[1].p.Y = m_vList[1].p.Y + dy;
    m_vList[2].p.X = m_vList[2].p.X + dx;
    m_vList[2].p.Y = m_vList[2].p.Y + dy;

    return *this;
}

bool MyDXObject::CreateVertexBuffer(ID3D11Device* pd3dDevice)
{
    // 버퍼 할당 크기를 세팅한다.
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(MyVertex) * m_vList.size();
    // 연결의 용도가 무엇인지 결정.
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    // 할당된 버퍼에
    // 시스템 메모리 -> GPU 로 데이터가 채워진다.
    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &m_vList.at(0);

    HRESULT hr = pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &this->m_pVertexBuffer);
    if (FAILED(hr))
        return false;

    return true;
}

bool MyDXObject::LoadShader(ID3D11Device* pd3dDevice)
{
    //ID3D11VertexShader* m_pVertexShader = nullptr;
    //ID3D11VertexShader* m_pPixelShader = nullptr;

    HRESULT hr;
    
    ID3DBlob* errorMsg = nullptr; // 컴파일러 오류 메세지
    hr = D3DCompileFromFile(
        L"VS.txt",
        nullptr,
        nullptr,
        "VS",
        "vs_5_0", // dx11 정점쉐이더 컴파일러
        0,
        0,
        &VS_Bytecode,
        &errorMsg);
    if (FAILED(hr))
    {
        MessageBoxA(NULL,
            (char*)errorMsg->GetBufferPointer(),
            "ERROR", MB_OK);
        return false;
    }

    // HLSL(High Level Shader Langauge)
    // 쉐이더(HLSL) 언어(컴파일 언어): C언어와 유사함.
    // HLSL 언어로 작성해서 컴파일을 하고 오브젝트를 사용한다.

    // 오브젝트 파일의 시작 주소
    const void* pShaderBytecode = VS_Bytecode->GetBufferPointer();
    // 오브젝트 파일의 크기
    SIZE_T BytecodeLength = VS_Bytecode->GetBufferSize();

    hr = pd3dDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, &m_pVertexShader);
    if (FAILED(hr))
        return false;
    if (errorMsg)
        errorMsg->Release();

    // 픽셀쉐이더 로드 및 생성
    hr = D3DCompileFromFile(
        L"PS.txt",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0", // dx11 픽셀쉐이더 컴파일러
        0,
        0,
        &PS_Bytecode,
        &errorMsg);
    if (FAILED(hr))
    {
        MessageBoxA(NULL,
            (char*)errorMsg->GetBufferPointer(),
            "ERROR", MB_OK);
        return false;
    }

    pShaderBytecode = PS_Bytecode->GetBufferPointer();
    BytecodeLength = PS_Bytecode->GetBufferSize();
    hr = pd3dDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, nullptr, &m_pPixelShader);
    if (FAILED(hr)) return false;

    return true;
}

// GPU 가 처리하는 순서
// 1) 지정된 정점버퍼에 접근하여
    // pContext->IASetVertexBuffers();
// 2) 1개의 정점 단위로 로드한다.
    // UINT pStrides = sizeof(MyVertex);
// 3) 지정된 인풋레이아웃에 따라서 정점 성분을 정점쉐이더에 전달한다.
// 정점쉐이더는 정점단위로 호출된다.
// |x, y, r, g, b, a|, |x, y, r, g, b, a|, |x, y, r, g, b, a|
//  0~7      8~11 
// |x, y, r, g, b, a, u, v|,  |x, y, r, g, b, a, u, v|,  |x, y, r, g, b, a, u, v|
//  0~7      8~11    24~25

bool MyDXObject::CreateInputLayout(ID3D11Device* pd3dDevice)
{
    //ID3D11InputLayout* m_pVertexLayout = nullptr;

    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POS",0, DXGI_FORMAT_R32G32_FLOAT,         0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEX",0, DXGI_FORMAT_R32G32_FLOAT,         0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    UINT NumElements = sizeof(layout) / sizeof(layout[0]);
    HRESULT hr = pd3dDevice->CreateInputLayout(
        layout,
        NumElements,
        VS_Bytecode->GetBufferPointer(),
        VS_Bytecode->GetBufferSize(),
        &m_pVertexLayout);
    if (FAILED(hr))
        return false;

    return true;
}

void MyDXObject::Render(ID3D11DeviceContext* pContext)
{
    //////////////////////
    // 렌더링 파이프라인 //
    /////////////////////
    
    // 사용하지 않는 파이프라인은 디폴트값 또는 null 사용된다.
    // pContext->HSSetShader(nullptr, nullptr, 0);
    // pContext->DSSetShader(nullptr, nullptr, 0);
    // pContext->GSSetShader(nullptr, nullptr, 0);
    // pContext->RSSetState(); // 디폴트 값 또는 null을 사용한다.
    
    // pContext->OMSetRenderTargets(1, &m_pRTV, nullptr); // MyCore 의 PreRender 에서 이미 설정함.

    UINT StartSlot = 0;
    UINT NumBuffers = 1;
    UINT pStrides = sizeof(MyVertex); // 1개의 정점 크기
    UINT pOffsets = 0; // 버퍼의 시작 인덱스
    // IASetVertexBuffers
    // m_pVertexBuffer를 사용해서 렌더링해라.
    // 1개의 정점의 크기(pStrides),
    // 버퍼에 시작 인덱스(pOffsets)로 부터
    // m_vList.size()의 정점을 사용해서 삼각형으로 렌더링 해라.
    // 's' 가 들어갔다는 것은 배열로 넣을 수 있다는 뜻
    // ID3D11Buffer* pBuffer[1] = { m_pVertexBuffer };
    pContext->IASetVertexBuffers(
        StartSlot,
        NumBuffers,
        &m_pVertexBuffer,
        &pStrides,
        &pOffsets);
    pContext->IASetInputLayout(m_pVertexLayout);
    pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pContext->VSSetShader(m_pVertexShader, nullptr, 0);
    pContext->PSSetShader(m_pPixelShader, nullptr, 0);
    
    // 위의 순서는 상관 없지만 Draw 명령이 떨어지기 전에는 반드시 설정되어있어야 한다.
    pContext->Draw(m_vList.size(), 0);
}

void MyDXObject::Release()
{
    if (VS_Bytecode)
    {
        VS_Bytecode->Release();
        VS_Bytecode = nullptr;
    }
    if (PS_Bytecode)
    {
        PS_Bytecode->Release();
        PS_Bytecode = nullptr;
    }

    if (m_pVertexBuffer)
    {
        m_pVertexBuffer->Release();
        m_pVertexBuffer = nullptr;
    }
    if (m_pVertexShader)
    {
        m_pVertexShader->Release();
        m_pVertexShader = nullptr;
    }
    if (m_pPixelShader)
    {
        m_pPixelShader->Release();
        m_pPixelShader = nullptr;
    }
    if (m_pVertexLayout)
    {
        m_pVertexLayout->Release();
        m_pVertexLayout = nullptr;
    }
}
