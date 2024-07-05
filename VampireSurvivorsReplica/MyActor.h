#pragma once
#include "MyDxObject.h"
#include "MyCollision.h"
#include "MySprite.h"
enum class UIStatus
{
	Default,
	Hover,
	Pressed,
	End,
};

// 씬에 배치 가능한 오브젝트 
// 움직임 기능이 없는 오브젝트
class MyActor : public MyDxObject
{
public:
	UIStatus m_usCurrentUIStatus = UIStatus::Default;

public:
	MySprite*			m_pSprite = nullptr;
public:
	MySpriteData		    m_SpriteData;
	void   SetAnim(float fAnimationTimer, MySprite* pSprite)
	{
		_ASSERT(pSprite);
		m_pSprite = pSprite;
		m_SpriteData = m_pSprite->m_SpriteData;

		m_SpriteData.m_iAnimIndex = 0;
		m_SpriteData.m_fAnimationTimer = fAnimationTimer;
		m_SpriteData.m_fChangeTime = m_SpriteData.m_fAnimationTimer / m_pSprite->m_SpriteData.m_fTexCounter;
	}
	//MyDxObject   m_dxObject;
	// 포함관계
	// 1) 렌더링 관리 컴포넌트
	// 2) 이동처리 관리 컴포넌트
	// 3) 충돌처리 관리 컴포넌트
public:
	bool				m_bDead= false;
	RECT				m_rt;
	MY_Math::FVector2	m_vPos;
	MY_Math::FMatrix     m_matWorld; // m_matCenter*m_matScale*m_matRotate*m_matTrans;
	MY_Math::FMatrix     m_matCenter;
	MY_Math::FMatrix     m_matTrans;
	MY_Math::FMatrix     m_matScale;
	MY_Math::FMatrix     m_matRotate;

	void    SetTrans(MY_Math::FVector2& p);
	void    SetScale(MY_Math::FVector2& v);
	void    SetRotate(float r);
	void    SetCenterMove(MY_Math::FVector2& p);
public:
	float				m_fSpeed = 300.0f;  // 속력	
	MY_Math::FVector2	m_vDirection = { 1.0f, 0.0f };
	MY_Math::FVector2	m_vOffset;
	MY_Math::FVector2	m_vVelocity; // 속도
public:
	virtual void    Frame() override;
	virtual void	SetVertexData(RECT rt) override;
	virtual MyActor& Move(float dx, float dy);
	virtual MyActor& Move(MY_Math::FVector2 d);
	virtual void	SetPos(MY_Math::FVector2& p);
	virtual void	SetPos(float& dx, float& dy);
	virtual void	SetWorldMatrix(MY_Math::FMatrix& m);

	virtual void	SetViewTransform(MY_Math::FMatrix& matCamera);
	virtual MyActor&	SetWorldTransform();
	virtual MyActor&	SetWorldTransform(MY_Math::FMatrix& m);

	virtual void    UpdateSprite();
	int			GetSpriteIndex();
	void    SetSpriteIndex(int index);
	virtual void    Render(ID3D11DeviceContext* pContext) override;
};


