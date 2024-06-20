#include "MyHero.h"

void   MyHero::SetVertexData(RECT rt)
{
	MyDxObject::SetVertexData(rt);

	// 0 [91] 400(w), 0 [1] ~ 300(h)
	POINT  imageSize = { 400, 300 };
	RECT texRT = { 91, 2, 91 + 40, 1 + 59 };
	// 91,1             131, 1

	// 91,61            131,61
	// 91,61            131,61
	m_vListScreen[0].t.X = (float)texRT.left / (float)imageSize.x;
	m_vListScreen[0].t.Y = (float)texRT.top / (float)imageSize.y;

	m_vListScreen[1].t = { (float)texRT.right / (float)imageSize.x, (float)texRT.top / (float)imageSize.y };
	m_vListScreen[2].t = { (float)texRT.right / (float)imageSize.x, (float)texRT.bottom / (float)imageSize.y };


	m_vListScreen[3].t = m_vListScreen[2].t;
	m_vListScreen[4].t = { (float)texRT.left / (float)imageSize.x, (float)texRT.bottom / (float)imageSize.y };
	m_vListScreen[5].t = m_vListScreen[0].t;

	m_vList = m_vListScreen;

	// �簢���� ���͸� ����������	
	m_vPos.X = (rt.left + rt.right) * 0.5f;
	m_vPos.Y = (rt.bottom + rt.top) * 0.5f;

	MY_Math::FVector2 vCenter = { -m_vPos.X, -m_vPos.Y };
	// �ʱ� ��ġ�� �������� �� ������ ��ġ�� �������� �Ѵ�.
	SetCenterMove(vCenter);
	SetTrans(m_vPos);
	m_rt = rt;
}

void  MyHero::Front()
{
	// �ð��� ����ȭ
	// �������� ��ȭ�� �����ϰ� �ð��� ������ �Ÿ��� �����δ�.)
	float fSpeed = m_fSpeed * g_fSecondPerFrame;
	// ������ ������ ������
	// q(���� ��ġ) = p(������ġ) + d(�̵�����:����ȭ)*s(ũ��);
	MY_Math::FVector2 p = m_vPos;
	MY_Math::FVector2 d = { 0.0f, -1.0f };
	MY_Math::FVector2 vOffset = d * fSpeed;
	//T_Math::FVector2 q = p + vOffset;		
	m_vPos = p + vOffset;
	m_vOffset += vOffset;
};
void  MyHero::Back()
{
	MY_Math::FVector2 d = { 0.0f, 1.0f };
	MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
	m_vPos = m_vPos + vOffset;
	m_vOffset += vOffset;
};
void  MyHero::Left()
{
	MY_Math::FVector2 d = { -1.0f, 0.0f };
	MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
	m_vPos = m_vPos + vOffset;
	m_vOffset += vOffset;
};
void  MyHero::Right()
{
	MY_Math::FVector2 d = { 1.0f, 0.0f };
	MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
	m_vPos = m_vPos + vOffset;
	m_vOffset += vOffset;
}
MyHero::MyHero()
{
	m_fSpeed = 100.0f;  // �ӷ�	
}