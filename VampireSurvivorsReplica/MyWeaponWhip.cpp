#include "MyWeaponWhip.h"

void   MyWeaponWhip::SetVertexData(RECT rt)
{
	MyDxObject::SetVertexData(rt);

	//// 0 [91] 400(w), 0 [1] ~ 300(h)
	//POINT  imageSize = { 400, 300 };
	//RECT texRT = { 91, 2, 91 + 40, 1 + 59 };
	//// 91,1             131, 1

	//// 91,61            131,61
	//// 91,61            131,61
	//m_vListScreen[0].t.X = (float)texRT.left / (float)imageSize.x;
	//m_vListScreen[0].t.Y = (float)texRT.top / (float)imageSize.y;

	//m_vListScreen[1].t = { (float)texRT.right / (float)imageSize.x, (float)texRT.top / (float)imageSize.y };
	//m_vListScreen[2].t = { (float)texRT.right / (float)imageSize.x, (float)texRT.bottom / (float)imageSize.y };


	//m_vListScreen[3].t = m_vListScreen[2].t;
	//m_vListScreen[4].t = { (float)texRT.left / (float)imageSize.x, (float)texRT.bottom / (float)imageSize.y };
	//m_vListScreen[5].t = m_vListScreen[0].t;

	//m_vList = m_vListScreen;

	// 사각형의 센터를 포지션으로	
	m_vPos.X = (rt.left + rt.right) * 0.5f;
	m_vPos.Y = (rt.bottom + rt.top) * 0.5f;

	MY_Math::FVector2 vCenter = { -m_vPos.X, -m_vPos.Y };
	// 초기 배치의 정점버퍼 각 정점의 위치를 중점으로 한다.
	SetCenterMove(vCenter);
	SetTrans(m_vPos);
	m_rt = rt;
}

void  MyWeaponWhip::Frame()
{
	m_vOffset = { 0.0f,0.0f };
	//if (I_Input.KeyCheck('W') == KEY_HOLD)
	//{
	//	//m_Cam.Up();
	//	Move({ 0.0f, -1.0f });
	//	//Front();
	//}
	//if (I_Input.KeyCheck('S') == KEY_HOLD)
	//{
	//	//m_Cam.Down();
	//	Move({ 0.0f, 1.0f });
	//	//Back();
	//}

	//if (I_Input.KeyCheck('D') == KEY_HOLD)
	//{
	//	Move({ 1.0f, 0.0f });
	//	//Right();		
	//	//m_Cam.Right(-hero.m_vOffset.X);
	//}
	//if (I_Input.KeyCheck('A') == KEY_HOLD)
	//{
	//	Move({ -1.0f, 0.0f });
	//	//hero.Left();		
	//}

	MyPawn::Frame();
}
MyWeaponWhip::MyWeaponWhip()
{
	m_fAnimDuration = 0.15f; // 애니메이션 지속시간 (공격 지속시간)
	m_fCooltime = 0.6f; // 애니메이션 사이의 간격 (공격 쿨타임)
}