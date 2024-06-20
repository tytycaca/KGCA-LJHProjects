#pragma once
#include "MyBaseManager.h"

class MyTexture : public MyResource
{
public:
	std::wstring m_csName;
	// ������ ����������(�ȼ����̴�)�� ���� ������
	ComPtr<ID3D11ShaderResourceView> m_pSRV = nullptr;
	// �ؽ�ó(�̹���) �ε� ������
	ComPtr<ID3D11Resource> m_pTexture = nullptr;

	void Release()
	{
		m_pSRV.Reset();
		m_pTexture.Reset();
	}

	bool Load(ID3D11Device* pd3dDevice, std::wstring filename)
	{
		HRESULT hr =
			DirectX::CreateWICTextureFromFile(
				pd3dDevice,
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

// MyTexture ��ü�� ����Ʈ�� �ϴ� �̱��� MyTexMgr ����
class MyTexMgr : public MyBaseManager<MyTexture, MyTexMgr>
{
	friend class MySingleton<MyTexMgr>;

private:
	MyTexMgr() {}
};
#define I_Tex MyTexMgr::Get()