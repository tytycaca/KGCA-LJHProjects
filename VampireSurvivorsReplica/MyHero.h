#pragma once
#include "MyPawn.h"
class MyHero : public MyPawn
{
public:
	bool m_bIsRight = true;
	bool m_bIsMove = false;
	float m_fEXP = 0.0f;

public:
	virtual void  Frame() override;
	void	SetVertexData(RECT rt) override;
	MyHero();
};
