#pragma once
#include "MyPawn.h"
class MyHero : public MyPawn
{
public:
	bool bIsRight = true;
	bool bIsMove = false;

public:
	virtual void  Frame() override;
	void	SetVertexData(RECT rt) override;
	MyHero();
};
