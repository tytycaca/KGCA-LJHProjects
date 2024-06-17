#pragma once
#include "MyStd.h"

// p, n, c, t
struct MyVertex
{
	MY_Math::FVector2 p; // ������ġ
	MY_Math::FVector4 c; // �����÷�
	MY_Math::FVector2 t; // �����ؽ�ó��ǥ
	MyVertex() = default;
	MyVertex(MY_Math::FVector2 p, MY_Math::FVector4 c, MY_Math::FVector2 t)
	{
		this->p = p;
		this->c = c;
		this->t = t;
	}
	MyVertex(float x, float y, float r, float g, float b, 
		float a, float u, float v)
	{
		this->p = { x, y };
		this->c = { r,g,b,a };
		this->t = { u, v };
	}
};
class MyDxObject 
{
protected:
	ID3D11Device*		 m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;

	// ������ ���̺����(�Ƚ����̴�)�� ���� ������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV = nullptr;	
	// �ؽ�ó(�̹���) �ε� ������
	ComPtr<ID3D11Resource> m_pTexture = nullptr;

public:
	std::vector<MyVertex>  m_vListScreen; // �ʱ� ȭ�� ����
	std::vector<MyVertex>  m_vList;		 // ������ ȭ�� ����
	std::vector<MyVertex>  m_vListNDC;	 // NDC
	std::wstring		   m_szShaderFilename;

public:
	MY_Math::FVector2 ConvertScreenToNDC(MY_Math::FVector2 v);
	virtual void UpdateVertexBuffer();
	virtual bool   Create(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		RECT rt, std::wstring texName,
		std::wstring hlsl);

	// GPU �޸𸮿� �Ҵ�� ����.
	ID3D11Buffer* m_pVertexBuffer=nullptr;
	bool     CreateVertexBuffer(ID3D11Device* pd3dDevice);
	
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* VS_Bytecode = nullptr; // ������Ʈ ����
	ID3DBlob* PS_Bytecode = nullptr; // ������Ʈ ����
	bool     LoadShader(ID3D11Device* pd3dDevice);

	ID3D11InputLayout* m_pVertexLayout = nullptr;
	bool     CreateInputLayout(ID3D11Device* pd3dDevice);
	virtual void	 Frame();
	virtual void     PreRender(ID3D11DeviceContext* pContext);
	virtual void     Render(ID3D11DeviceContext* pContext);
	virtual void     PostRender(ID3D11DeviceContext* pContext);
	virtual void     Release();

	virtual void	SetVertexData(RECT rt);
};

