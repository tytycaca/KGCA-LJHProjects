#pragma once
#include "TDevice.h"
#include "DirectXTex.h"

// ������Ʈ �Ӽ��� ��Ŀ�� �Է¿� �߰����Ӽ� d3d11.lib; d3dcompiler.lib; DirectXTex.lib;
// �־���� ���� #pragma comment �� �̿��ϸ� ������Ʈ�� ������ �� �ִ�.
#pragma comment (lib, "DirectXTex.lib")

struct TVector2
{
	float x;
	float y;
	TVector2() { x = 0; y = 0; }
	TVector2(float _x, float _y) { x = _x; y = _y; }
};

struct TVector3
{
	float x;
	float y;
	float z;
	TVector3() { x = 0; y = 0; z = 0; }
	TVector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};

struct TVector4
{
	float x;
	float y;
	float z;
	float w;
	TVector4() { x = 0; y = 0; z = 0; w = 0; }
	TVector4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};

struct TVertex
{
	TVector2 tex;
	TVector3 pos;
	TVector4 color;

	TVertex() {};
	TVertex(TVector2 t, TVector3 p, TVector4 c) { tex = t; pos = p; color = c; }
};

class Sample : public TDevice
{
	std::unique_ptr<DirectX::ScratchImage> m_tex;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	std::vector<TVertex>  m_VertexList;
	std::vector<DWORD>    m_IndexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3DBlob* m_pVertexShaderCode = nullptr; // �����ϵ� ����Ʈ �ڵ�
	ID3DBlob* m_pPixelShaderCode = nullptr; // �����ϵ� ����Ʈ �ڵ�
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pVertexlayout = nullptr;

public:
	bool    Init()		override;
	bool    Render()	override;
	bool    Release()	override;
	
	bool LoadTexture(std::wstring texFileName);

	ID3D11Buffer* CreateBuffer(UINT, UINT, void**, HRESULT*);
	bool CreateVertexShader();
	bool CreatePixelShader();
	bool CreateInputLayout();
};