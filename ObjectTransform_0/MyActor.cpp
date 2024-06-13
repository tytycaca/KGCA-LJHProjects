#include "MyActor.h"

void    MyActor::Frame()
{
	Transform(m_matWorld);
}

void    MyActor::SetPos(MY_Math::FVector2& p)
{
	m_vPos = p;
	m_matWorld._31 = m_vPos.X;
	m_matWorld._32 = m_vPos.Y;
}

void    MyActor::SetPos(float& dx, float& dy)
{
	m_vPos.X = dx;
	m_vPos.Y = dx;
}

void MyActor::SetWorld(MY_Math::FMatrix& m)
{
	m_matWorld = m;
}

MyActor& MyActor::Transform(MY_Math::FMatrix& m)
{
	for (int iv = 0; iv < m_vListScreen.size(); iv++)
	{
		m_vList[iv].p = m_vListScreen[iv].p * m;
	}
	UpdateVertexBuffer();
	return *this;
}

MyActor& MyActor::Trans(MY_Math::FMatrix& m)
{
	//for (int iv = 0; iv < m_vListScreen.size(); iv++)
	//{
	//	m_vListScreen[iv].p = m_vListScreen[iv].p * m;		
	//}
	//UpdateVertexBuffer();
	return *this;
}

void   MyActor::SetVertexData(RECT rt)
{
	MyDxObject::SetVertexData(rt);

	// �簢���� ���͸� ����������
	//m_vPos.X = (rt.left + rt.right) * 0.5f;
	//m_vPos.Y = (rt.bottom + rt.top) * 0.5f;
	// ���� ��� �𼭸��� ����������
	m_vPos.X = rt.left;
	m_vPos.Y = rt.top;

	m_rt = rt;
}

MyActor& MyActor::Move(float dx, float dy)
{
	// ȭ����ǥ��
	for (auto& v : m_vListScreen)
	{
		v.p += { dx, dy };
	}
	m_vPos = { dx,dy };

	UpdateVertexBuffer();
	return *this;
}

MyActor& MyActor::Move(MY_Math::FVector2 d)
{
	MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
	m_vPos += vOffset;
	m_vOffset += vOffset;

	float halfW = (m_rt.right - m_rt.left) * 0.5f;
	float halfH = (m_rt.bottom - m_rt.top) * 0.5f;

	m_rt.left = m_vListScreen[0].p.X;
	m_rt.right = m_vListScreen[1].p.X;
	m_rt.top = m_vListScreen[0].p.Y;
	m_rt.bottom = m_vListScreen[2].p.Y;
	return *this;
}