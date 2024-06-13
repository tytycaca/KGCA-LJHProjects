#pragma once
#include "MyDxObject.h"
#include "MyCollision.h"

// 움직임 기능이 없는 오브젝트
class MyActor : public MyDxObject
{
public:
	bool				m_bDead = false;
	RECT				m_rt;
	MY_Math::FVector2	m_vPos;
	MY_Math::FMatrix	m_matWorld;

public:
	float				m_fSpeed = 300.0f; // 속력
	MY_Math::FVector2	m_vDirection = { 1.0f, 1.0f };
	MY_Math::FVector2	m_vOffset;
	MY_Math::FVector2	m_vVelocity; // 속도

public:
	virtual void    Frame() override;
	virtual void	SetVertexData(RECT rt) override;
	virtual MyActor& Move(float dx, float dy);
	virtual MyActor& Move(MY_Math::FVector2 d);
	MyActor& Trans(MY_Math::FMatrix& m);

	virtual void	SetPos(MY_Math::FVector2& p);
	virtual void	SetPos(float& dx, float& dy);
	virtual void	SetWorld(MY_Math::FMatrix& m);

protected:
	MyActor& Transform(MY_Math::FMatrix& m);
};