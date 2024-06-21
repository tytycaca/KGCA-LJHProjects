#include "MyDxObject.h"

void MyDxObject::UpdateVertexBuffer()
{
	// NDC ��ǥ�� ��ȯ
	for (int i = 0; i < m_vList.size(); i++)
	{
		m_vListNDC[i].p = ConvertScreenToNDC(m_vList[i].p);
		m_vListNDC[i].c = m_vList[i].c;
		m_vListNDC[i].t = m_vList[i].t;
	}
	if (m_pVertexBuffer != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_vListNDC.at(0), 0, 0);
	}
}

MY_Math::FVector2 MyDxObject::ConvertScreenToNDC(MY_Math::FVector2 v)
{
	// 0~ 800 -> 0 ~ 1
	v.X = v.X / g_xClientSize;
	v.Y = v.Y / g_yClientSize;
	//NDC ��ǥ��
	// 0 ~ 1  -> -1 ~ +1
	MY_Math::FVector2 ret;
	ret.X = v.X * 2.0f - 1.0f;
	ret.Y = -(v.Y * 2.0f - 1.0f);


	// -1 ~ 1  -> 0 ~ +1
	/*v.X = v.X * 0.5f + 0.5f;
	v.Y = v.Y * 0.5f + 0.5f;*/
	return ret;
}

void MyDxObject::SetVertexData(RECT rt)
{
	m_vListScreen.resize(6);
	// �ð�������� ����Ǿ�� �Ѵ�.
	m_vListScreen[0] = { (float)rt.left, (float)rt.top,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
	m_vListScreen[1] = { MY_Math::FVector2(rt.right, rt.top),
					MY_Math::FVector4(1, 1, 1, 1),
					MY_Math::FVector2(1, 0) };
	m_vListScreen[2] = { MY_Math::FVector2(rt.right, rt.bottom),
					MY_Math::FVector4(1, 1, 1, 1),
					MY_Math::FVector2(1, 1) };
	m_vListScreen[3] = { MY_Math::FVector2(rt.right, rt.bottom),
					MY_Math::FVector4(1, 1, 1, 1),
					MY_Math::FVector2(1, 1) };
	m_vListScreen[4] = { MY_Math::FVector2(rt.left, rt.bottom),
					MY_Math::FVector4(1, 1, 1, 1),
					MY_Math::FVector2(0, 1) };
	m_vListScreen[5].p = MY_Math::FVector2(rt.left, rt.top);
	m_vListScreen[5].c = MY_Math::FVector4(0, 0, 1, 1);
	m_vListScreen[5].t = MY_Math::FVector2(0, 0);

	// ȭ����ǥ�踦  NDC��ǥ �����Ѵ�.
	m_vList = m_vListScreen;
	m_vListNDC = m_vListScreen;

	UpdateVertexBuffer();
}

bool   MyDxObject::Create(
	ID3D11Device* pd3dDevice,	
	ID3D11DeviceContext* pContext,
	RECT rt, std::wstring texName,
	std::wstring hlsl)
{

	// ������ ������ �ּ� ��ȯ : m_pSRV.GetAddressOf();
	// ������ �ּ� :m_pSRV.Get();

	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
	m_szShaderFilename = hlsl;

	m_pTexture = I_Tex.Load(texName).get();
	if (m_pTexture != nullptr)
	{
		m_pSRV = m_pTexture->m_pSRV;
	}

	SetVertexData(rt);

	if (CreateVertexBuffer(m_pd3dDevice) == false)
	{
		Release();
		return false;
	}
	if (LoadShader(m_szShaderFilename) == false)
	{
		Release();
		return false;
	}
	if (CreateInputLayout(m_pd3dDevice) == false)
	{
		Release();
		return false;
	}
	return true;
}
bool     MyDxObject::CreateVertexBuffer(ID3D11Device* pd3dDevice)
{
	// ���� �Ҵ� ũ�⸦ �����Ѵ�.
	D3D11_BUFFER_DESC  bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(MyVertex) * m_vListScreen.size();
	// ���ῡ �뵵�� ����? 
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;


	// �Ҵ�� ���ۿ� 
	// �ý��۸޸𸮰� ->GPU�޸𸮷� ü������ ������
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_vListNDC.at(0);

	HRESULT hr = pd3dDevice->CreateBuffer(
		&bd,
		&sd,
		&this->m_pVertexBuffer);
	if (FAILED(hr)) return false;
	return true;
}
bool     MyDxObject::LoadShader(std::wstring filename)
{
	m_pShader = I_Shader.Load(filename).get();
	if (m_pShader == nullptr) return false;
	return true;
}
// GPU �� ó���ϴ� ����
// 1) ������ �������ۿ� �����Ͽ� 
	// pContext->IASetVertexBuffers(StartSlot, NumBuffers, &m_pVertexBuffer, &pStrides, &pOffsets);
// 2) 1���� ���� ������ �ε��Ѵ�.UINT pStrides = sizeof(MyVertex); // 1���� ���� ũ��
// 3) ������ ��ǲ���̾ƿ��� ���� ���� ������ �������̴��� �����Ѵ�
// �������̴��� ���������� ȣ��ȴ�.
// |x, y, r,g,b,a|,|x, y, r,g,b,a| ,|x, y, r,g,b,a| ,|x, y, r,g,b,a| 
//   0~7  8~11
// |x, y, r,g,b,a, u,v|,|x, y, r,g,b,a, u,v| ,|x, y, r,g,b,a, u,v| ,|x, y, r,g,b,a, u,v| 
//   0~7  8~11   24~32
bool     MyDxObject::CreateInputLayout(ID3D11Device* pd3dDevice)
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
{"POS",0,	DXGI_FORMAT_R32G32_FLOAT,		0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,	0,8,D3D11_INPUT_PER_VERTEX_DATA,0 },
{"TEX",0,DXGI_FORMAT_R32G32_FLOAT,		    0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = pd3dDevice->CreateInputLayout(
		layout,
		NumElements,
		m_pShader->VS_Bytecode->GetBufferPointer(),
		m_pShader->VS_Bytecode->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void MyDxObject::Frame()
{
	
}

void MyDxObject::PreRender(ID3D11DeviceContext* pContext)
{
	// ������� �ʴ� ������������ ����Ʈ �� �Ǵ� null���ȴ�.	
	UINT StartSlot = 0;
	UINT NumBuffers = 1;
	UINT pStrides = sizeof(MyVertex); // 1���� ���� ũ��
	UINT pOffsets = 0; // ���ۿ� ���� �ε���
	pContext->IASetVertexBuffers(StartSlot, NumBuffers, &m_pVertexBuffer, &pStrides, &pOffsets);
	pContext->IASetInputLayout(m_pVertexLayout);
	pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 0�� �������� �ؽ�ó ����
	pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());
	//Texture2D g_txTexture : register(t0);

	pContext->VSSetShader(m_pShader->m_pVertexShader, nullptr, 0);
	pContext->PSSetShader(m_pShader->m_pPixelShader, nullptr, 0);
}

void MyDxObject::PostRender(ID3D11DeviceContext* pContext)
{
	pContext->Draw(m_vListScreen.size(), 0);
}

void     MyDxObject::Render(ID3D11DeviceContext* pContext)
{
	PreRender(pContext);
	PostRender(pContext);
}

void MyDxObject::Release()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
	if (m_pVertexLayout)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}
}