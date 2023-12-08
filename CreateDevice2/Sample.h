#pragma once
#include "TDevice.h"


struct TVertex
{
	float x;
	float y;
	float z;
	TVertex() { x = 0; y = 0; z = 0; }
	// z의 성분은 0 ~ 1 범위로 되어 있다.
	TVertex(float _x, float _y, float _z = 0.5f) { x = _x; y = _y; z = _z; }
};

class Sample : public TDevice
{
	std::vector<TVertex>  m_VertexList;
	std::vector<DWORD>    m_IndexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3DBlob* m_pVertexShaderCode = nullptr; // 컴파일된 바이트 코드
	ID3DBlob* m_pPixelShaderCode = nullptr; // 컴파일된 바이트 코드
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pVertexlayout = nullptr;

public:
	bool    Init()		override;
	bool    Render()	override;
	bool    Release()	override;
	ID3D11Buffer* CreateBuffer(UINT, UINT, void**, HRESULT*);
	bool CreateVertexShader();
	bool CreatePixelShader();
	bool CreateInputLayout();
};