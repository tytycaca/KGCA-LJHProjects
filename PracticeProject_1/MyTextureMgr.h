#pragma once
#include "MyStd.h"
#include "DirectXTex.h"
// ������Ʈ �Ӽ� -> c++ -> �Ϲ� -> �߰� ���� ���͸��� ../../DxTex/include �߰�
// ������Ʈ �Ӽ� -> ��Ŀ -> �Ϲ� -> �߰� ���̺귯�� ���͸��� ../../lib �߰�


// �ؽ��� �ν��Ͻ� �����̳�, ���ҽ��� ���� �� �ؽ��� �ε� ���� Ŭ����
class MyTexture
{
// ����Ʈ������(unique_ptr)�� ScratchImage �ν��Ͻ� �����̳� ���� (DirectXTex ���̺귯�� ���� �����̳�)
// 
// ���ҽ� �� : ������ ���ӱ�. �ڿ��� ������ ���������ο� ���� �� ���̴� ��ü(����� ����)
//			    -> ���������δ� �ڿ��� ���� Ư���� �ð��� �����Ѵٰ� �����ϸ� ��
// 
// ���̴� ���ҽ� �並 �����Ͽ� ������ ������������ ���̴� �ܰ谡 �ڿ��� ���� �� �ְ� ��
public:
	std::unique_ptr<DirectX::ScratchImage> m_tex;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;

public:
	// DDS, TGA, WIC, HDR �ؽ��� ���� �ε� �Լ�
	bool Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, std::wstring texFileName);
	bool Release();

};


// �ؽ��� std::map �� ����Ͽ� �ؽ��İ� �ߺ��ε����� �ʰ� �������ִ� �Ŵ��� Ŭ����
// �̱��� �������� ���� (static ���� ���� �� ������ privateȭ)
class MyTextureMgr
{
private:
	// ����̽�, ����̽� ���ؽ�Ʈ ���
	//  -> TextureMgr �� ����� ������ setter �� ����Ͽ� �Ҵ��� ���� (GameCore Ŭ��������)
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dContext = nullptr;

public:
	// MyTextureMgr ��ü getter (�̱���)
	static MyTextureMgr& Get()
	{
		// MyTextureMgr ��ü ���� (�̱���)
		static MyTextureMgr textureMgr;
		return textureMgr;
	}

	// device, deviceContext ��ü setter
	void set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext)
	{
		m_pd3dDevice = pd3dDevice;
		m_pd3dContext = pd3dContext;
	}

public:
	// �ؽ�ó �ߺ� �ε� üũ�� std::map
	std::map<std::wstring, std::shared_ptr<MyTexture>> m_map;
	// �ؽ�ó �ߺ� �ε� ���� üũ �� �ε��ϴ� �Լ�
	MyTexture* Load(std::wstring loadFileName);
	bool Release();

private:
	// ������ privateȭ (�̱���)
	MyTextureMgr() {};

public:
	~MyTextureMgr();
};

