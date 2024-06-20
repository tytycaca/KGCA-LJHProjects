#pragma once
#include "MyBaseManager.h"

class MyShader : public MyResource
{
public:
	std::wstring m_csName;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* VS_Bytecode = nullptr; // 오브젝트 파일
	ID3DBlob* PS_Bytecode = nullptr; // 오브젝트 파일

public:
	void Release()
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
	}

	bool Load(ID3D11Device* pd3dDevice, std::wstring filename)
	{
		m_csName = filename;
		HRESULT hr;
		ID3DBlob* errormsg = nullptr; // 컴파일 중 오류 메세지

		hr = D3DCompileFromFile(
			filename.c_str(),
			nullptr,
			nullptr,
			"VSMain",
			"vs_5_0", // dx11 정점쉐이더 컴파일러
			0,
			0,
			&VS_Bytecode,
			&errormsg
		);
		if (FAILED(hr))
		{
			MessageBoxA(NULL,
				(char*)errormsg->GetBufferPointer(),
				"ERROR", MB_OK);
			return false;
		}

		// 오브젝트 파일의 시작주소
		const void* pShaderBytecode = VS_Bytecode->GetBufferPointer();
		// 오브젝트 파일의 크기
		SIZE_T BytecodeLength = VS_Bytecode->GetBufferSize();

		hr = pd3dDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, &m_pVertexShader);

		if (FAILED(hr))
		{
			return false;
		}
		if (errormsg) errormsg->Release();

		/// 픽쉘쉐이더 로드 및 생성	
		hr = D3DCompileFromFile(
			filename.c_str(),
			nullptr,
			nullptr,
			"PSMain",
			"ps_5_0", // dx11 정점쉐이더 컴파일러
			0,
			0,
			&PS_Bytecode,
			&errormsg
		);
		if (FAILED(hr))
		{
			MessageBoxA(NULL,
				(char*)errormsg->GetBufferPointer(),
				"ERROR", MB_OK);
			return false;
		}

		pShaderBytecode = PS_Bytecode->GetBufferPointer();
		BytecodeLength = PS_Bytecode->GetBufferSize();
		hr = pd3dDevice->CreatePixelShader(PS_Bytecode->GetBufferPointer(),
			PS_Bytecode->GetBufferSize(), nullptr, &m_pPixelShader);
		if (FAILED(hr)) return false;
		return true;
	}
};

class MyShaderMgr : public MyBaseManager<MyShader, MyShaderMgr>
{
	friend class MySingleton<MyShaderMgr>;

private:
	MyShaderMgr() {}
};
#define I_Shader MyShaderMgr::Get()