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
    // ���� �Ҵ� ũ�⸦ �����Ѵ�.
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(MyVertex) * m_vList.size();
    // ������ �뵵�� �������� ����.
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    // �Ҵ�� ���ۿ�
    // �ý��� �޸� -> GPU �� �����Ͱ� ä������.
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
    
    ID3DBlob* errorMsg = nullptr; // �����Ϸ� ���� �޼���
    hr = D3DCompileFromFile(
        L"VS.txt",
        nullptr,
        nullptr,
        "VS",
        "vs_5_0", // dx11 �������̴� �����Ϸ�
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
    // ���̴�(HLSL) ���(������ ���): C���� ������.
    // HLSL ���� �ۼ��ؼ� �������� �ϰ� ������Ʈ�� ����Ѵ�.

    // ������Ʈ ������ ���� �ּ�
    const void* pShaderBytecode = VS_Bytecode->GetBufferPointer();
    // ������Ʈ ������ ũ��
    SIZE_T BytecodeLength = VS_Bytecode->GetBufferSize();

    hr = pd3dDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, &m_pVertexShader);
    if (FAILED(hr))
        return false;
    if (errorMsg)
        errorMsg->Release();

    // �ȼ����̴� �ε� �� ����
    hr = D3DCompileFromFile(
        L"PS.txt",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0", // dx11 �ȼ����̴� �����Ϸ�
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

// GPU �� ó���ϴ� ����
// 1) ������ �������ۿ� �����Ͽ�
    // pContext->IASetVertexBuffers();
// 2) 1���� ���� ������ �ε��Ѵ�.
    // UINT pStrides = sizeof(MyVertex);
// 3) ������ ��ǲ���̾ƿ��� ���� ���� ������ �������̴��� �����Ѵ�.
// �������̴��� ���������� ȣ��ȴ�.
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
    // ������ ���������� //
    /////////////////////
    
    // ������� �ʴ� ������������ ����Ʈ�� �Ǵ� null ���ȴ�.
    // pContext->HSSetShader(nullptr, nullptr, 0);
    // pContext->DSSetShader(nullptr, nullptr, 0);
    // pContext->GSSetShader(nullptr, nullptr, 0);
    // pContext->RSSetState(); // ����Ʈ �� �Ǵ� null�� ����Ѵ�.
    
    // pContext->OMSetRenderTargets(1, &m_pRTV, nullptr); // MyCore �� PreRender ���� �̹� ������.

    UINT StartSlot = 0;
    UINT NumBuffers = 1;
    UINT pStrides = sizeof(MyVertex); // 1���� ���� ũ��
    UINT pOffsets = 0; // ������ ���� �ε���
    // IASetVertexBuffers
    // m_pVertexBuffer�� ����ؼ� �������ض�.
    // 1���� ������ ũ��(pStrides),
    // ���ۿ� ���� �ε���(pOffsets)�� ����
    // m_vList.size()�� ������ ����ؼ� �ﰢ������ ������ �ض�.
    // 's' �� ���ٴ� ���� �迭�� ���� �� �ִٴ� ��
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
    
    // ���� ������ ��� ������ Draw ����� �������� ������ �ݵ�� �����Ǿ��־�� �Ѵ�.
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
