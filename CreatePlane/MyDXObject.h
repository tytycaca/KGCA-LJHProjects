#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")

#include <vector>
#include "MyMath.h"

struct MyVertex
{
	MY_Math::FVector2 v;
};

class MyDXObject
{
public:
	// 시스템 메모리에 할당된 버퍼.
	std::vector<MyVertex> m_vList;
	MyDXObject& Move(float dx, float dy);
	bool CreateVertexBuffer(ID3D11Device* pd3dDevice);
	bool LoadShader(ID3D11Device* pd3dDevice);
	bool CreateInputLayout(ID3D11Device* pd3dDevice);
	void Render(ID3D11DeviceContext* pContext);
	void Release();

public:
	// GPU 메모리에 할당된 버퍼.
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3DBlob* VS_Bytecode = nullptr; // 오브젝트 파일
	ID3DBlob* PS_Bytecode = nullptr; // 오브젝트 파일
};

