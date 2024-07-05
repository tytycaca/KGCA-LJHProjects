#pragma once
#include "MyPawn.h"
class MyHero : public MyPawn
{
public:
	MY_Math::FVector2 m_vInitPos = MY_Math::FVector2(0, 0);
	float m_fWidth = 0.0f;
	float m_fHeight = 0.0f;
	bool m_bIsRight = true;
	bool m_bIsMove = false;
	float m_fEXP = 0.0f;
	int m_iCharLv = 1;

public:
	virtual void  Frame() override;
	void	SetVertexData(RECT rt) override;
	MyHero();
};
