#include "MyActor.h"
void    MyActor::Render(ID3D11DeviceContext* pContext)
{
	MyDxObject::PreRender(pContext);
	if (m_pSprite != nullptr)
	{
		pContext->PSSetShaderResources(0, 1,m_pSprite->GetSRV(m_SpriteData.m_iAnimIndex).GetAddressOf());
	}
	MyDxObject::PostRender(pContext);
}
void    MyActor::Frame()
{
	m_matWorld = m_matCenter * m_matScale * m_matRotate * m_matTrans;
	SetWorldTransform();
	//m_vOffset = { 0.0f,0.0f };
}
void    MyActor::UpdateSprite()
{
	if (m_pSprite != nullptr)
	{
		m_pSprite->Update(m_SpriteData);
		if (m_pSprite->m_vList.size() > 0)
		{
			for (int iV = 0; iV < 6; iV++)
			{
				m_vList[iV].t = m_pSprite->m_vList[iV].t;
			}
		}
	}
}
void    MyActor::UpdateSpriteWithColor(float r, float g, float b, float a)
{
	if (m_pSprite != nullptr)
	{
		m_pSprite->Update(m_SpriteData);
		if (m_pSprite->m_vList.size() > 0)
		{
			for (int iV = 0; iV < 6; iV++)
			{
				m_vList[iV].t = m_pSprite->m_vList[iV].t;
				m_vList[iV].c.X = r;
				m_vList[iV].c.Y = g;
				m_vList[iV].c.Z = b;
				m_vList[iV].c.W = a;
			}
		}
	}
}
int    MyActor::GetSpriteIndex()
{
	return m_pSprite->GetSpriteIndex(m_SpriteData);
}
void    MyActor::SetSpriteIndex(int index)
{
	m_pSprite->SetSpriteIndex(m_SpriteData, index);
}

void    MyActor::SetTrans(MY_Math::FVector2& p)
{
	m_matTrans.Translation(p);
}
void    MyActor::SetScale(MY_Math::FVector2& s)
{
	m_matScale.Scale(s);
}
void    MyActor::SetRotate(float r)
{
	m_matRotate.rotate(r);
}
void    MyActor::SetCenterMove(MY_Math::FVector2& p)
{	
	m_matCenter.Translation(p);	
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
void MyActor::SetWorldMatrix(MY_Math::FMatrix& m)
{
	m_matWorld = m;
}
void MyActor::SetViewTransform(MY_Math::FMatrix& matCamera)
{	
	for (int iv = 0; iv < m_vListScreen.size(); iv++)
	{
		m_vList[iv].p = m_vList[iv].p * matCamera;
	}
}
MyActor& MyActor::SetWorldTransform()
{
	for (int iv = 0; iv < m_vListScreen.size(); iv++)
	{
		m_vList[iv].p = m_vListScreen[iv].p * m_matWorld;
	}
	return *this;
}
MyActor& MyActor::SetWorldTransform(MY_Math::FMatrix& m)
{
	for (int iv = 0; iv < m_vListScreen.size(); iv++)
	{
		m_vList[iv].p = m_vListScreen[iv].p * m;
	}
	return *this;
}
void   MyActor::SetVertexData(RECT rt)
{
	MyDxObject::SetVertexData(rt);

	// 사각형의 센터를 포지션으로	
	m_vPos.X = (rt.left + rt.right) * 0.5f;
	m_vPos.Y = (rt.bottom + rt.top) * 0.5f;

	MY_Math::FVector2 vCenter = { -m_vPos.X, -m_vPos.Y };
	// 초기 배치의 정점버퍼 각 정점의 위치를 중점으로 한다.
	SetCenterMove(vCenter);
	SetTrans(m_vPos);
	m_rt = rt;
}
MyActor& MyActor::Move(float dx, float dy)
{
	Move({dx,dy});
	//// 화면좌표계
	//for (auto& v : m_vListScreen)
	//{
	//	v.p += { dx, dy };
	//}
	//m_vPos = { dx,dy };

	//UpdateVertexBuffer();
	return *this;
}
MyActor& MyActor::Move(MY_Math::FVector2 d)
{
	MY_Math::FVector2 vOffset = d * m_fSpeed * g_fSecondPerFrame;
	m_vPos += vOffset;
	m_vOffset += vOffset;

	SetTrans(m_vPos);

	m_rt.left	= m_vList[0].p.X;
	m_rt.right	= m_vList[1].p.X;
	m_rt.top	= m_vList[0].p.Y;
	m_rt.bottom = m_vList[2].p.Y;
	return *this;
}