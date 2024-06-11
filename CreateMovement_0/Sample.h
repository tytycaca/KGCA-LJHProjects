#pragma once
#include "MyCore.h"
#include "MyActer.h"

class Sample : public MyCore
{
	MyActer objScreen; // »ï°¢Çü
	std::vector<MyActer> m_UIList;
	std::vector<MyNpc> m_npcList;
	MyHero hero;
	UINT m_iNpcCounter = 0;
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pNumber;

public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;

};