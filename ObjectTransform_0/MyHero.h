#pragma once
#include "MyPawn.h"

class MyHero : public MyPawn
{
public:
	virtual void  Frame();
	virtual void  Front();
	virtual void  Back();
	virtual void  Left();
	virtual void  Right();
	MyHero();
};

