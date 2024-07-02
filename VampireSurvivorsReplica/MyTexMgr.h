#pragma once
#include "MyBaseManager.h"
#include "WicTextureLoader.h"
#include "DDSTextureLoader.h"

class MyTexture : public MyResource
{
	ID3D11Device* m_pd3dDevice = nullptr;
public:
	virtual void Set(ID3D11Device* pDevice) override
	{
		m_pd3dDevice = pDevice;
	};
public:
	D3D11_TEXTURE2D_DESC td;
	std::wstring m_csName;
	// ������ ���̺����(�Ƚ����̴�)�� ���� ������
	ComPtr<ID3D11ShaderResourceView> m_pSRV = nullptr;
	// �ؽ�ó(�̹���) �ε� ������
	ComPtr<ID3D11Resource> m_pTexture = nullptr;
public:
	void Release();
	bool Load(std::wstring filename);
};
// TTexture��ü�� ����Ʈ�� �ϴ� �̱��� MyTexMgr ����
class MyTexMgr : public MyBaseManager<MyTexture,MyTexMgr>
{
	friend class MySingleton<MyTexMgr>;
private:
	MyTexMgr(){}
};
#define I_Tex MyTexMgr::Get()
