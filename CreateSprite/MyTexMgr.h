#pragma once
#include "MyBaseManager.h"

class MyTexture : public MyResource
{
private:
	ID3D11Device* m_pd3dDevice = nullptr;

public:
	virtual void Set(ID3D11Device* pDevice) override
	{
		m_pd3dDevice = pDevice;
	};

public:
	std::wstring m_csName;
	// 렌더링 파이프라인(픽셀쉐이더)에 전송 데이터
	ComPtr<ID3D11ShaderResourceView> m_pSRV = nullptr;
	// 텍스처(이미지) 로드 데이터
	ComPtr<ID3D11Resource> m_pTexture = nullptr;

	void Release()
	{
		m_pSRV.Reset();
		m_pTexture.Reset();
	}

	bool Load(std::wstring filename)
	{
		HRESULT hr =
			DirectX::CreateWICTextureFromFile(
				m_pd3dDevice,
				filename.c_str(),
				m_pTexture.GetAddressOf(),//&m_pTexture
				m_pSRV.GetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}
};

// MyTexture 객체를 리스트로 하는 싱글톤 MyTexMgr 생성
class MyTexMgr : public MyBaseManager<MyTexture, MyTexMgr>
{
	friend class MySingleton<MyTexMgr>;

private:
	MyTexMgr() {}
};
#define I_Tex MyTexMgr::Get()