#include "MyHero.h"

void  MyHero::Front()
{
	// 시간의 동기화
	// 프레임의 변화를 무시하고 시간당 일정한 거리로 움직인다.)
	float fSpeed = m_fSpeed * g_fSecondPerFrame;
	// 벡터의 직선의 방정식
	// q(계산된 위치) = p(현재위치) + d(이동방향:정규화)*s(크기);
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
	m_fSpeed = 100.0f;  // 속력	
}