#include "MyHero.h"

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