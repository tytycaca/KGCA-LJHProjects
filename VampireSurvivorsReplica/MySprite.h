#pragma once
#include "MyDxObject.h"
struct myRECT
{
	float    left;
	float    top;
	float    right;
	float    bottom;
};
// �ֿ���
// 1) �ؽ�ó ��ü, UI��ü : ������ �ð����� 
// 2) ������ ������ ��ü

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
	std::vector<MyVertex>  m_vList;		 // ������ ȭ�� ����
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
	// UV��������Ʈ
	std::vector<RECT_ARRAY>		m_rtSpriteList;
	// �ؽ�ó ��������Ʈ
	std::vector<STRING_VECTOR>	m_szSpriteList;
	// Grid ��������Ʈ
	std::vector<POINT>			m_ptSpriteList;
public:
	bool Load(const TCHAR* pszLoad);
	bool GameDataLoad(const TCHAR* pszLoad);
	MySprite* GetPtr(W_STR name);
};
#define I_Sprite MySpriteManager::Get()