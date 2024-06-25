#pragma once
#include "MyScene.h"
class MySceneIngame :   public MyScene
{
public:
	UINT		m_iLevel = 1;
	using T_Effect = std::shared_ptr<MySprite>;
	std::vector<T_Effect>  m_EffectList;
	
	MySound* m_pEffectSound = nullptr;
	TCamera				m_Cam;
	MyActor				objScreen; // »ï°¢Çü
	std::vector<MyActor> m_UIList;
	std::vector<MyNpc>	m_npcList;
	MyHero hero;
	UINT  m_iNpcCounter = 0;
	void    LevelUp(UINT iNpc);
public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;
public:
	void  SetSound();
	void  SetUI();
	void  SetPlayer();
};

