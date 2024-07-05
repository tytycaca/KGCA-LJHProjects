#pragma once
#include "MyPawn.h"

class MyWeaponWhip : public MyPawn
{
public:
	bool m_bIsRight = true;
	float m_fAnimDuration = 0.15f;
	float m_fCooltime = 0.6f;
	float m_fCooltimeCounter = 0.0f;
	int m_iCurrentSpriteIndex = 0;

public:
	virtual void  Frame() override;
	void	SetVertexData(RECT rt) override;
	MyWeaponWhip();
};
