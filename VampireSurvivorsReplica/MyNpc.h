#pragma once
#include "MyPawn.h"
class MyNpc : public MyPawn
{

public:
	virtual void     Frame();
	void	SetVertexData(RECT rt) override;
	MyNpc();
};