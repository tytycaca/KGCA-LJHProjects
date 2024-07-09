#pragma once
#include "MyScene.h"
class MySceneIngame :   public MyScene
{
public:
	UINT		m_iMonsterNum = 25;
	UINT		m_iCurrentStage = 1;
	float		m_fMonsterScaleOffset = 0.0f;
	float		m_fMonsterDMGOffset = 0.0f;
	using T_Effect = std::shared_ptr<MySprite>;
	std::vector<T_Effect>  m_EffectList;
	std::shared_ptr<MySound> m_attackSound = nullptr;
	
	MySound* m_pEffectSound = nullptr;
	TCamera				m_Cam;
	MyActor				objScreen; // »ï°¢Çü

	std::vector<MyActor> m_UIList;
	std::vector<MyNpc>	m_npcList;
	MyHero hero;
	std::shared_ptr<MyWeaponWhip> m_pWeaponWhip = std::make_shared<MyWeaponWhip>();
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
	void  SetWeaponWhip();
};

