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

// ���� ��ġ ������ ������Ʈ 
// ������ ����� ���� ������Ʈ
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
	// ���԰���
	// 1) ������ ���� ������Ʈ
	// 2) �̵�ó�� ���� ������Ʈ
	// 3) �浹ó�� ���� ������Ʈ
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
	float				m_fSpeed = 300.0f;  // �ӷ�	
	MY_Math::FVector2	m_vDirection = { 1.0f, 0.0f };
	MY_Math::FVector2	m_vOffset;
	MY_Math::FVector2	m_vVelocity; // �ӵ�
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


