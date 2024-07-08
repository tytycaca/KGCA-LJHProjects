#pragma once
#include "MyPawn.h"
class MyNpc : public MyPawn
{
public:
	float m_fDMG = 20.0f;
	float m_fEXP = 20.0f;
	std::wstring m_Name = L"MonsterBat";

public:
	virtual void     Frame();
	void	SetVertexData(RECT rt) override;
	MyNpc();
};