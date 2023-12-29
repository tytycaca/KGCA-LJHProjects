#pragma once
#include "MyStd.h"
#include "DirectXTex.h"
// 프로젝트 속성 -> c++ -> 일반 -> 추가 포함 디렉터리에 ../../DxTex/include 추가
// 프로젝트 속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉터리에 ../../lib 추가


// 텍스쳐 인스턴스 컨테이너, 리소스뷰 생성 및 텍스쳐 로딩 구현 클래스
class MyTexture
{
// 스마트포인터(unique_ptr)로 ScratchImage 인스턴스 컨테이너 생성 (DirectXTex 라이브러리 내부 컨테이너)
// 
// 리소스 뷰 : 일종의 접속기. 자원을 렌더링 파이프라인에 묶는 데 쓰이는 객체(어댑터 역할)
//			    -> 개념적으로는 자원에 대한 특정한 시각을 제공한다고 생각하면 됨
// 
// 셰이더 리소스 뷰를 생성하여 렌더링 파이프라인의 셰이더 단계가 자원을 읽을 수 있게 함
public:
	std::unique_ptr<DirectX::ScratchImage> m_tex;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;

public:
	// DDS, TGA, WIC, HDR 텍스쳐 파일 로드 함수
	bool Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, std::wstring texFileName);
	bool Release();

};


// 텍스쳐 std::map 을 사용하여 텍스쳐가 중복로딩되지 않게 관리해주는 매니저 클래스
// 싱글톤 패턴으로 구현 (static 으로 생성 후 생성자 private화)
class MyTextureMgr
{
private:
	// 디바이스, 디바이스 컨텍스트 멤버
	//  -> TextureMgr 을 사용할 곳에서 setter 을 사용하여 할당할 것임 (GameCore 클래스에서)
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dContext = nullptr;

public:
	// MyTextureMgr 객체 getter (싱글톤)
	static MyTextureMgr& Get()
	{
		// MyTextureMgr 객체 생성 (싱글톤)
		static MyTextureMgr textureMgr;
		return textureMgr;
	}

	// device, deviceContext 객체 setter
	void set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext)
	{
		m_pd3dDevice = pd3dDevice;
		m_pd3dContext = pd3dContext;
	}

public:
	// 텍스처 중복 로딩 체크용 std::map
	std::map<std::wstring, std::shared_ptr<MyTexture>> m_map;
	// 텍스처 중복 로딩 여부 체크 후 로드하는 함수
	MyTexture* Load(std::wstring loadFileName);
	bool Release();

private:
	// 생성자 private화 (싱글톤)
	MyTextureMgr() {};

public:
	~MyTextureMgr();
};

