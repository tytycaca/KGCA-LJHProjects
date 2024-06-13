#include "Sample.h"

void   Sample::Init()
{
	MY_Math::FMatrix m1;
	MY_Math::FMatrix m2;
	MY_Math::FMatrix m3 = m1 * m2;
	MY_Math::FMatrix matTrans;
	MY_Math::FMatrix matScale;
	matTrans.Translation({ 100, 20 });
	matScale.Scale({ 2, 0.5f });
	MY_Math::FMatrix matRotate;
	matRotate.Rotate(TBASIS_PI / 2.0f);

	std::wstring texPath = L"../../data/"; //0.png
	for (int iTex = 0; iTex < 10; iTex++)
	{
		std::wstring texFileName = texPath +
			std::to_wstring(iTex) + L".png";
		ComPtr<ID3D11ShaderResourceView> texSRV;
		//ComPtr<ID3D11Resource> m_pTexture = nullptr;
		HRESULT hr =
			DirectX::CreateWICTextureFromFile(
				m_pd3dDevice.Get(),
				texFileName.c_str(),
				nullptr,
				texSRV.GetAddressOf());
		m_pNumber.push_back(texSRV);
	}

	MY_Math::FVector2 a = { 10.0f, 0.0f };
	MY_Math::FVector2 b = { 0.0f, 10.0f };
	float fDot = a | b;
	float fAngle = a.Angle(b);

	RECT rtBk = { 0, 0, g_xClientSize, g_yClientSize };
	objScreen.Create(m_pd3dDevice.Get(), m_pContext, rtBk, L"bk.bmp");

	m_UIList.resize(3);

	m_UIList[0].Create(m_pd3dDevice.Get(), m_pContext, { 0, 0, 100, 100 }, L"kgca1.png");
	m_UIList[1].Create(m_pd3dDevice.Get(), m_pContext, { 700, 0, 800, 100 }, L"kgca2.png");
	m_UIList[2].Create(m_pd3dDevice.Get(), m_pContext, { 700, 500, 800, 600 }, L"kgca3.png");
	hero.Create(m_pd3dDevice.Get(), m_pContext, { 350, 250, 450, 350 }, L"Peach.png");
	hero.m_fSpeed = 500.0f;

	// �̵���ȯ
	m_UIList[0].Trans(matTrans);

	// �̵� ��ȯ
	//for (int iv = 0; iv < m_UIList[0].m_vListScreen.size(); iv++)
	//{
	//	// 1 by 3	*	3 by 2	=>	1 by 2
	//	MY_Math::FVector2 p = m_UIList[0].m_vListScreen[0].p;
	//	/*MY_Math::FVector2 ret = p * matTrans;
	//	MY_Math::FVector2 ret = matTrans.Multiply(p);*/
	//	MY_Math::FVector2 ret;
	//	ret.X = p.X * matTrans.m[0][0] +
	//			p.Y * matTrans.m[1][0] +
	//			1.0f * matTrans.m[2][0];
	//	ret.Y = p.X * matTrans.m[0][1] +
	//			p.Y * matTrans.m[1][1] +
	//			1.0f * matTrans.m[2][1];
	//	m_UIList[0].m_vListScreen[iv].p = ret;
	//}
	//m_UIList[0].UpdateVertexBuffer();

	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		MyNpc npc;
		MY_Math::FVector2 pos;
		pos.X = randstep(0.0f, g_xClientSize);
		pos.Y = randstep(0.0f, g_yClientSize);
		npc.Create(m_pd3dDevice.Get(), m_pContext, { (LONG)pos.X, (LONG)pos.Y, (LONG)(pos.X + 50.0f), (LONG)(pos.Y + 50.0f) }, L"watermelon.png");
		m_npcList.push_back(npc);
	}
	
	m_iNpcCounter = m_npcList.size();
}

void   Sample::Frame()
{
	MY_Math::FVector2 vPos = { 400.0f, 300.0f };
	vPos.X = 400.0f;// *(cos(g_fGameTime) * 0.5f + 0.5f);
	vPos.Y = 300.0f;// *(cos(g_fGameTime) * 0.5f + 0.5f);
	//objScreen.SetPos(vPos);

	MY_Math::FMatrix matWorld;
	MY_Math::FMatrix matTrans;
	MY_Math::FMatrix matScale;
	MY_Math::FMatrix matRotate;
	matTrans.Translation(vPos);
	matRotate.Rotate(g_fGameTime);// DegreeToRadian(g_fGameTime));
	MY_Math::FVector2 vScale = {
		(float)cos(g_fGameTime) * 0.5f + 0.5f,
		(float)cos(g_fGameTime) * 0.5f + 0.5f };
	matScale.Scale(vScale);

	MY_Math::FMatrix matCenter;
	MY_Math::FVector2 vCenter = { -800.0f * 0.5f, -600.0f * 0.5f };
	matCenter.Translation(vCenter);
	matWorld = matCenter * matScale * matRotate * matTrans;// *matRotate* matTrans;
	//matWorld._31 = matTrans._31;
	//matWorld._32 = matTrans._32;
	objScreen.SetWorld(matWorld);

	objScreen.Frame();

	//for (auto& ui : m_UIList)
	//{
	//	if (MyCollision::RectToPt(ui.m_rt, m_Input.m_ptMousePos))
	//	{
	//		ui.m_bDead = true;
	//	}
	//}

	//for (auto& npc : m_npcList)
	//{
	//	if (npc.m_bDead == false && MyCollision::RectToRect(npc.m_rt, hero.m_rt))
	//	{
	//		npc.m_bDead = true;
	//		m_iNpcCounter = max(1, m_iNpcCounter - 1);
	//	}
	//}

	//if (m_Input.KeyCheck('W') == KEY_HOLD)
	//{
	//	hero.Move({ 0.0f, -1.0f });
	//	//hero.Front();
	//}
	//if (m_Input.KeyCheck('S') == KEY_HOLD)
	//{
	//	hero.Move({ 0.0f, 1.0f });
	//	//hero.Back();
	//}
	//if (m_Input.KeyCheck('A') == KEY_HOLD)
	//{
	//	hero.Move({ -1.0f, 0.0f });
	//	//hero.Left();
	//}
	//if (m_Input.KeyCheck('D') == KEY_HOLD)
	//{
	//	hero.Move({ 1.0f, 0.0f });
	//	//hero.Right();
	//}

	//hero.Frame();
	//for (int iNpc = 0; iNpc < m_npcList.size(); iNpc++)
	//{
	//	m_npcList[iNpc].Frame();
	//}
}

void   Sample::Render()
{
	objScreen.Render(m_pContext);

	/*for_each(begin(m_UIList), end(m_UIList), [&](auto& obj)
		{
			if (!obj.m_bDead)
			{
				obj.PreRender(m_pContext);
				m_pContext->PSSetShaderResources(0, 1, m_pNumber[m_iNpcCounter - 1].GetAddressOf());
				obj.PostRender(m_pContext);
			}
		});
	
	bool bGameEnding = true;
	hero.Render(m_pContext);
	for (int iNpc = 0; iNpc < m_npcList.size(); iNpc++)
	{
		if (!m_npcList[iNpc].m_bDead)
		{
			m_npcList[iNpc].Render(m_pContext);
			bGameEnding = false;
		}
	}
	m_bGameRun = !bGameEnding;*/
}

void   Sample::Release()
{
	objScreen.Release();
	for (auto& obj : m_UIList)
	{
		obj.Release();
	}
	hero.Release();
	for (int iNpc = 0; iNpc < m_npcList.size(); iNpc++)
	{
		m_npcList[iNpc].Release();
	}
}

T_GAME_START(800, 600);