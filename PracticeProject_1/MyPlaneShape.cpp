#include "MyPlaneShape.h"

bool MyPlaneShape::CreateVertexBuffer()
{
	UINT iSize = m_VertexList.size() * sizeof(MyVertex);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	// 메모리 할당 크기, 버퍼의 저장소 및 접근권한 설정, 버퍼의 용도
	bd.ByteWidth = iSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 하위 리소스를 초기화하기 위한 데이터를 지정
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	// 초기화 데이터에 대한 포인터
	sd.pSysMem = &m_VertexList.at(0);

	HRESULT hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::CreateIndexBuffer()
{
	UINT iSize = m_IndexList.size() * sizeof(DWORD);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	// 메모리 할당 크기, 버퍼의 저장소 및 접근권한 설정, 버퍼의 용도
	bd.ByteWidth = iSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 하위 리소스를 초기화하기 위한 데이터를 지정
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	// 초기화 데이터에 대한 포인터
	sd.pSysMem = &m_IndexList.at(0);

	HRESULT hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::CreateVertexShader()
{
	ID3DBlob* ppErrorMsgs = nullptr;
	HRESULT hr = D3DCompileFromFile(
		m_csDefaultVSFileName.c_str(),
		nullptr,
		nullptr,
		m_csDefaultVSEntryName.c_str(),
		"vs_5_0",
		0,
		0,
		&m_pVertexShaderByteCode,
		&ppErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)ppErrorMsgs->GetBufferPointer(), "Error", MB_OK);
		if (ppErrorMsgs) ppErrorMsgs->Release();
		return false;
	}
	if (ppErrorMsgs) ppErrorMsgs->Release();

	hr = m_pd3dDevice->CreateVertexShader(
		m_pVertexShaderByteCode->GetBufferPointer(),
		m_pVertexShaderByteCode->GetBufferSize(),
		nullptr,
		&m_pVertexShader);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::CreatePixelShader()
{
	ID3DBlob* ppErrorMsgs = nullptr;
	HRESULT hr = D3DCompileFromFile(
		m_csDefaultPSFileName.c_str(),
		nullptr,
		nullptr,
		m_csDefaultPSEntryName.c_str(),
		"ps_5_0",
		0,
		0,
		&m_pPixelShaderByteCode,
		&ppErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)ppErrorMsgs->GetBufferPointer(), "Error", MB_OK);
		if (ppErrorMsgs) ppErrorMsgs->Release();
		return false;
	}
	if (ppErrorMsgs) ppErrorMsgs->Release();

	hr = m_pd3dDevice->CreatePixelShader(
		m_pPixelShaderByteCode->GetBufferPointer(),
		m_pPixelShaderByteCode->GetBufferSize(),
		nullptr,
		&m_pPixelShader);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::CreateInputLayout()
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	// 인풋엘리먼트 디스크립션의 개수 계산: 디스크립션마다 크기가 같기 때문에 첫번째 원소의 사이즈로 전체를 나누면 된다
	UINT iNumLayout = sizeof(layout) / sizeof(layout[0]);
	// 선언한 모든 인풋디스크립션이 D3D11_INPUT_PER_VERTEX_DATA 을 사용중이기 때문에 vertexshader 로 처리하면 된다
	HRESULT hr = m_pd3dDevice->CreateInputLayout(
		layout,
		iNumLayout,
		m_pVertexShaderByteCode->GetBufferPointer(),
		m_pVertexShaderByteCode->GetBufferSize(),
		&m_pVertexlayout);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::LoadTexture(W_STR texFileName)
{
	m_pTexture = MyTextureMgr::Get().Load(texFileName);
	if (m_pTexture == nullptr)
		return false;

	return true;
}

bool MyPlaneShape::LoadTexture(T_STR_VECTOR texFileArray)
{
	for (int i = 0; i < texFileArray.size(); i++)
	{
		m_pTextureArr.push_back(MyTextureMgr::Get().Load(texFileArray[i]));
	}
	if (m_pTextureArr.empty())
		return false;

	return true;
}

bool MyPlaneShape::Create(W_STR name, W_STR texFileName)
{
	m_csName = name;
	if (!texFileName.empty())
	{
		if (!LoadTexture(texFileName))
		{
			return false;
		}
	}

	m_IndexList.push_back(0);
	m_IndexList.push_back(1);
	m_IndexList.push_back(2);

	m_IndexList.push_back(2);
	m_IndexList.push_back(3);
	m_IndexList.push_back(0);

	if (!CreateVertexBuffer() || !CreateIndexBuffer())
	{
		return false;
	}
	if (!CreateVertexShader() || !CreatePixelShader())
	{
		return false;
	}

	if (!CreateInputLayout())
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::Create(W_STR name, T_STR_VECTOR texFileArray)
{
	m_csName = name;
	if (!texFileArray.empty())
	{
		if (!LoadTexture(texFileArray))
		{
			return false;
		}
	}

	m_IndexList.push_back(0);
	m_IndexList.push_back(1);
	m_IndexList.push_back(2);

	m_IndexList.push_back(2);
	m_IndexList.push_back(3);
	m_IndexList.push_back(0);

	if (!CreateVertexBuffer() || !CreateIndexBuffer())
	{
		return false;
	}
	if (!CreateVertexShader() || !CreatePixelShader())
	{
		return false;
	}

	if (!CreateInputLayout())
	{
		return false;
	}

	return true;
}

bool MyPlaneShape::Init()
{
	m_csDefaultVSFileName = L"../../data/shader/shader.txt";
	m_csDefaultPSFileName = L"../../data/shader/shader.txt";
	m_csDefaultVSEntryName = "VS";
	m_csDefaultPSEntryName = "PS";
	return true;
}

bool MyPlaneShape::Frame()
{
	return true;
}

bool MyPlaneShape::PreRender()
{
	m_pd3dContext->PSSetShaderResources(0, 1, &m_pTexture->m_pTextureSRV);
	m_pd3dContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pd3dContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pd3dContext->IASetInputLayout(m_pVertexlayout);
	m_pd3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	UINT pStrides = sizeof(MyVertex);
	UINT pOffsets = 0;
	m_pd3dContext->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&pStrides,
		&pOffsets);
	m_pd3dContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

bool MyPlaneShape::PostRender()
{
	m_pd3dContext->DrawIndexed(m_IndexList.size(), 0, 0);
	return true;
}

bool MyPlaneShape::Render()
{
	PreRender();
	PostRender();
	return true;
}

bool MyPlaneShape::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pVertexShaderByteCode) m_pVertexShaderByteCode->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShaderByteCode) m_pPixelShaderByteCode->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pVertexlayout) m_pVertexlayout->Release();

	return true;
}