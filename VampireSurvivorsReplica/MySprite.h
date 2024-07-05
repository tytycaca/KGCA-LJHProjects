#pragma once
#include "MyDxObject.h"
struct myRECT
{
	float    left;
	float    top;
	float    right;
	float    bottom;
};
// 주요기능
// 1) 텍스처 교체, UI교체 : 정해진 시간동안 
// 2) 렌더링 영역의 교체

struct MySpriteData
{
	int		m_iAnimIndex = 0;
	float	m_fPlayTimer = 0.0f;
	float	m_fAnimationTimer = 0.0f;
	float	m_fChangeTime = 0.0f;
	float   m_fTexCounter = 1.0f;
};
class MySprite 
{
public:
	W_STR			m_csName;
	std::vector<MyVertex>  m_vList;		 // 프레임 화면 정보
	MyTexture*		m_pTex = nullptr;
public:
	MySpriteData		m_SpriteData;
public:
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pSRVList;
	std::vector<RECT> m_pUVList;
	std::vector<myRECT> m_tUVList;

	ComPtr<ID3D11ShaderResourceView> GetSRV();
	ComPtr<ID3D11ShaderResourceView> GetSRV(UINT index);
	void   SetAnim(float fAnimationTimer)
	{
		m_SpriteData.m_iAnimIndex = 0;
		m_SpriteData.m_fAnimationTimer = fAnimationTimer;
		m_SpriteData.m_fChangeTime = m_SpriteData.m_fAnimationTimer / m_SpriteData.m_fTexCounter;
	}
	void   Update(MySpriteData& data);
	int    GetSpriteIndex(MySpriteData& data);
	void   SetSpriteIndex(MySpriteData& data, int index);
public:
	void  Load(STRING_VECTOR& iconList);
	void  Load(std::wstring path, RECT_ARRAY& list);

	void  Load(std::wstring* iconList, UINT iCount);
	void  Load(std::wstring path, UINT xSize, UINT ySize);
public:
	MySprite();
};
class MySpriteUV : public MySprite
{
public:
	MySpriteUV() = default;
};
class MySpriteTex : public MySprite
{
public:
	MySpriteTex() = default;
};
class MySpriteManager : public MySingleton<MySpriteManager>
{
public:
	std::map<std::wstring, std::unique_ptr<MySprite>> m_List;
public:
	std::vector<UINT>  m_iSpriteTypeList;
	std::vector<W_STR> m_SpriteNameList;
	std::vector<W_STR> m_TextureNameList;
	std::vector<W_STR> m_MaskTextureNameList;
	std::vector<W_STR> m_ShaderNameList;
	// UV스프라이트
	std::vector<RECT_ARRAY>		m_rtSpriteList;
	// 텍스처 스프라이트
	std::vector<STRING_VECTOR>	m_szSpriteList;
	// Grid 스프라이트
	std::vector<POINT>			m_ptSpriteList;
public:
	bool Load(const TCHAR* pszLoad);
	bool GameDataLoad(const TCHAR* pszLoad);
	MySprite* GetPtr(W_STR name);
};
#define I_Sprite MySpriteManager::Get()