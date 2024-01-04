#pragma once
#include "MyPlaneShape.h"

struct MyInitSet
{
	W_STR name;
	W_STR szMaskTex;
	MyVector2 p;
	MyVector2 uvPos;
	MyVector2 size;
	float    fMaxSpeed = 300.0f;
};

class MyPlayerObj : public MyPlaneShape
{
	MyInitSet	m_InitSet;

public:
	MyVector2    m_vPos;
	MyVector2    m_vDirection;
	MyVector2    m_vVelocity;
	float       m_fAccel; // 가속도 크기
	float		m_fSpeed; // speed(속력,스칼라), velocity(속도, 벡터)
	MyTexture* m_ptexMask = nullptr;

public:
	bool   CreateVertexBuffer() override;
	bool   Frame() override;
	bool   PreRender() override;

public:
	bool   Create(MyInitSet info, W_STR texFileName);
	bool   SetVB(MyVector2 p, MyVector2 uvPos, MyVector2 size, MyVector2 texSize);
	void   SetPosion(MyVector2 p);
	void   SetPosion(float x, float y);

public:
	MyPlayerObj();
};

