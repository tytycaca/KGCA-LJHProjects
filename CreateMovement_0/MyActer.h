#pragma once
#include "MyDxObject.h"
#include "MyCollision.h"

// 움직임 기능이 없는 오브젝트
class MyActer : public MyDxObject
{
public:
	bool				m_bDead = false;
	RECT				m_rt;
	MY_Math::FVector2	m_vPos;

public:
	float				m_fSpeed = 300.0f; // 속력
	MY_Math::FVector2	m_vDirection = { 1.0f, 1.0f };
	MY_Math::FVector2	m_vOffset;
	MY_Math::FVector2	m_vVelocity; // 속도

public:
	virtual void	SetVertexData(RECT rt) override;
	MyActer&		Move(float dx, float dy);
};

// 움직임 기능이 있는 오브젝트
class MyPawn : public MyActer
{
public:
	virtual void  Move(MY_Math::FVector2 d)
	{
		MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
		m_vPos += vOffset;
		m_vOffset += vOffset;

		float halfW = (m_rt.right - m_rt.left) * 0.5f;
		float halfH = (m_rt.bottom - m_rt.top) * 0.5f;

		m_rt.left = m_vList[0].p.X;
		m_rt.right = m_vList[1].p.X;
		m_rt.top = m_vList[0].p.Y;
		m_rt.bottom = m_vList[2].p.Y;
	}
};

class MyHero : public MyPawn
{
public:
	virtual void Frame() override
	{
		// 화면 좌표계
		for (auto& v : m_vList)
		{
			v.p += m_vOffset;
		}

		// NDC 좌표계 변환
		for (int i = 0; i < m_vList.size(); i++)
		{
			m_vListNDC[i].p = ConvertScreenToNDC(m_vList[i].p);
		}
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_vListNDC.at(0), 0, 0);

		m_vOffset = { 0.0f, 0.0f };
	}

	virtual void Front()
	{
		// 시간의 동기화(프레임의 변화를 무시하고 시간당 일정한 거리로 움직인다.)
		float fSpeed = m_fSpeed * g_fSecondPerFrame;
		// 벡터의 직선의 방정식
		// q(계산된 위치) = p(현재 위치) + d(이동 방향: 정규화된 벡터) * s(크기);
		MY_Math::FVector2 p = m_vPos;
		MY_Math::FVector2 d = { 0.0f, -1.0f };
		MY_Math::FVector2 vOffset = d * fSpeed; // 프레임 이동값
		//MY_Math::FVector2 q = p + m_vOffset;
		m_vPos = p + vOffset;
		m_vOffset += vOffset;
	}
	virtual void Back()
	{
		MY_Math::FVector2 d = { 0.0f, 1.0f };
		MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
		m_vPos = m_vPos + vOffset;
		m_vOffset += vOffset;
	}
	virtual void Left()
	{
		MY_Math::FVector2 d = { -1.0f, 0.0f };
		MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
		m_vPos = m_vPos + vOffset;
		m_vOffset += vOffset;
	}
	virtual void Right()
	{
		MY_Math::FVector2 d = { 1.0f, 0.0f };
		MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
		m_vPos = m_vPos + vOffset;
		m_vOffset += vOffset;
	}
	MyHero()
	{
		m_fSpeed = 100.0f;
	}
};

class MyNpc : public MyPawn
{
public:
	virtual void Frame() override
	{
		if (m_vPos.X > g_xClientSize)
		{
			m_vDirection.X *= -1.0f;
			m_vPos.X = g_xClientSize;
		}
		if (m_vPos.X < 0)
		{
			m_vDirection.X *= -1.0f;
			m_vPos.X = 0;
		}
		if (m_vPos.Y > g_yClientSize)
		{
			m_vDirection.Y *= -1.0f;
			m_vPos.Y = g_yClientSize;
		}

		if (m_vPos.Y < 0)
		{
			m_vDirection.Y *= -1.0f;
			m_vPos.Y = 0;
		}

		Move(m_vDirection);

		// 화면 좌표계
		for (auto& v : m_vList)
		{
			v.p += m_vOffset;
		}

		// NDC 좌표계 변환
		for (int i = 0; i < m_vList.size(); i++)
		{
			m_vListNDC[i].p = ConvertScreenToNDC(m_vList[i].p);
		}
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_vListNDC.at(0), 0, 0);

		m_vOffset = { 0.0f, 0.0f };
	}

	MyNpc()
	{
		m_fSpeed = randstep(100.0f, 300.0f);
		m_vDirection.X = randstep(-1.0f, 1.0f);
		m_vDirection.Y = randstep(-1.0f, 1.0f);
	}
};
