#pragma once
#include "MyPawn.h"
class MyHero : public MyPawn
{
public:
	virtual void  Frame() override;
	virtual void  Front();
	virtual void  Back();
	virtual void  Left();
	virtual void  Right();
	void	SetVertexData(RECT rt) override;
	MyHero();
};
