#include "MySceneIngame.h"
#include "MyStd.h"
#include "MyInput.h"
void   MySceneIngame::SetSound()
{	
	m_pBGSound = I_Sound.Load(L"../../data/sound/romance.mid");
	if (m_pBGSound)
	{
		//m_pBGSound->Play(true);
	}
	m_pEffectSound = I_Sound.Load(L"../../data/sound/GunShot.mp3").get();

}
void   MySceneIngame::SetUI()
{
	RECT rtBG = { -640, -360, 1920, 1080 };
	objScreen.Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext, rtBG,
		L"../../resource/BG_Library.png",
		L"../../data/shader/Default.txt");
	objScreen.m_pSprite = nullptr;

	m_UIList.resize(4);
	m_UIList[0].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext, { 0, 0, 100, 100 },
		L"../../data/kgca1.png",
		L"Alphablend.hlsl");
	m_UIList[0].SetAnim(1.0f, I_Sprite.GetPtr(L"DefalultNumber"));

	m_UIList[1].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext, { 1180, 0, 1280, 100 },
		L"../../data/kgca1.png",
		L"Alphablend.hlsl");
	m_UIList[1].SetAnim(20.0f, I_Sprite.GetPtr(L"IconList"));

	m_UIList[2].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 1180, 620, 1280, 720 },
		L"../../data/kgca1.png",
		L"Alphablend.hlsl");
	m_UIList[2].SetAnim(1.0f, I_Sprite.GetPtr(L"Fog"));

	m_UIList[3].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 0, 620, 100, 720 },
		L"../../data/Effect/slashFire_4x4.png",
		L"Alphablend.hlsl");
	m_UIList[3].SetAnim(2.0f, I_Sprite.GetPtr(L"wik"));
}
void   MySceneIngame::SetPlayer()
{
	//DrawRect = { 91, 1, 91+40, 1+60 }
	hero.Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext, { 615, 335, 665, 385 },
		L"../../resource/Antonio_01.png",
		L"Alphablend.hlsl");
	//hero.SetAnim(0.5f, I_Sprite.GetPtr(L"Antonio"));
	hero.m_fSpeed = 500.0f;
}
void    MySceneIngame::LevelUp(UINT iLevel)
{
	Sleep(1000);
	std::vector<std::wstring> spriteName =
	{
		L"DefalultNumber",
		L"wik",
		L"rtClash",
		L"IconList",
		L"rtBomb",
		L"rtExplosion",
	};

	hero.m_vPos.X = 640.0f;
	hero.m_vPos.Y = 360.0f;
	m_Cam.m_vCameraPos = { 0.0f,0.0f };
	for (int iNpc = 0; iNpc < iLevel; iNpc++)
	{
		MyNpc npc;
		MY_Math::FVector2 pos;
		pos.X = randstep(0.0f, g_xClientSize);
		pos.Y = randstep(0.0f, g_yClientSize);
		npc.Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
			{ (LONG)pos.X, (LONG)pos.Y,(LONG)(pos.X + 67.0f), (LONG)(pos.Y + 78.0f) },
			L"../../data/Sprite/bitmap1Alpha.bmp",
			L"Alphablend.hlsl");

		npc.SetAnim(1.0f, I_Sprite.GetPtr(spriteName[m_iLevel % spriteName.size()]));
		m_npcList.push_back(npc);
	}
	m_iNpcCounter = m_npcList.size();
}
void   MySceneIngame::Init()
{
	SetSound();
	SetUI();
	SetPlayer();
	LevelUp(m_iLevel);
}
void    MySceneIngame::Frame()
{

	if (m_iNpcCounter <= 9)
	{
		if (I_Input.KeyCheck(VK_F1) == KEY_PUSH)
		{
			MyNpc npc;
			MY_Math::FVector2 pos;
			pos.X = randstep(0.0f, g_xClientSize);
			pos.Y = randstep(0.0f, g_yClientSize);
			npc.Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
				{ (LONG)pos.X, (LONG)pos.Y,(LONG)(pos.X + 67.0f), (LONG)(pos.Y + 78.0f) },
				L"../../data/Sprite/bitmap1Alpha.bmp",
				L"Alphablend.hlsl");
			npc.SetAnim(1.0f, I_Sprite.GetPtr(L"DefalultNumber"));
			m_npcList.push_back(npc);
			m_iNpcCounter = m_npcList.size();
		}
	}

	//MY_Math::FVector2 vPos = objScreen.m_vPos;
	//MY_Math::FVector2 vScale = { (float)cos(g_fGameTime) * 0.5f + 0.5f, (float)cos(g_fGameTime) * 0.5f + 0.5f };
	//MY_Math::FVector2 vCenter = { -800.0f * 0.5f, -600.0f * 0.5f };

	////objScreen.SetCenterMove(vCenter);
	////objScreen.SetScale(vScale);
	////objScreen.SetRotate(g_fGameTime);
	////objScreen.SetTrans(vPos);
	objScreen.Frame();


	for (auto& ui : m_UIList)
	{
		if (MyCollision::RectToPt(ui.m_rt, I_Input.m_ptMousePos))
		{
			MY_Math::FVector2 vScale = { 0.7f + (float)cos(g_fGameTime * 5) * 0.5f + 0.5f,
										0.7f + (float)cos(g_fGameTime * 5) * 0.5f + 0.5f };
			ui.SetScale(vScale);
			ui.SetRotate(g_fGameTime);
			ui.SetTrans(ui.m_vPos);
		}
		ui.Frame();
	}

	for (auto& npc : m_npcList)
	{
		npc.Frame();
		if (npc.m_bDead == false && MyCollision::RectToRect(npc.m_rt, hero.m_rt))
		{
			npc.m_bDead = true;
			m_iNpcCounter = max(0, m_iNpcCounter - 1);
		}
	}
	for (auto iter = m_npcList.begin(); iter != m_npcList.end(); )
	{
		if ((*iter).m_bDead == true)
		{
			iter = m_npcList.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	if (I_Input.KeyCheck('A') == KEY_HOLD)
	{
		hero.bIsMove = true;
		if (hero.m_vPos.X - 25 > objScreen.m_rt.left)
		{
			hero.Move({ -1.0f,0.0f });
		}
	}
	if (I_Input.KeyCheck('D') == KEY_HOLD)
	{
		hero.bIsMove = true;
		if (hero.m_vPos.X + 25 < objScreen.m_rt.right)
		{
			hero.Move({ 1.0f,0.0f });
		}
	}
	if (I_Input.KeyCheck('W') == KEY_HOLD)
	{
		hero.bIsMove = true;
		if (hero.m_vPos.Y - 25 > objScreen.m_rt.top + 375)
		{
			hero.Move({ 0.0f,-1.0f });
		}
	}
	if (I_Input.KeyCheck('S') == KEY_HOLD)
	{
		hero.bIsMove = true;
		if (hero.m_vPos.Y + 25 < objScreen.m_rt.bottom - 375)
		{
			hero.Move({ 0.0f,1.0f });
		}
	}

	if (I_Input.KeyCheck('W') == KEY_UP)
		hero.bIsMove = false;
	if (I_Input.KeyCheck('S') == KEY_UP)
		hero.bIsMove = false;
	if (I_Input.KeyCheck('A') == KEY_UP)
		hero.bIsMove = false;
	if (I_Input.KeyCheck('D') == KEY_UP)
		hero.bIsMove = false;

	/*if (hero.bIsRight)
	{
		hero.SetAnim(0.5f, I_Sprite.GetPtr(L"Antonio"));
	}
	else
	{
		hero.SetAnim(0.5f, I_Sprite.GetPtr(L"AntonioReversed"));
	}*/

	if (hero.m_vPos.X < 0)
		m_Cam.m_vCameraPos.X = g_xClientSize / 2;
	else if (hero.m_vPos.X > g_xClientSize)
		m_Cam.m_vCameraPos.X = -(int)(g_xClientSize / 2);
	else
		m_Cam.m_vCameraPos.X = -hero.m_vPos.X + g_xClientSize / 2;

	if (hero.m_vPos.Y < 0)
		m_Cam.m_vCameraPos.Y = g_yClientSize / 2;
	else if (hero.m_vPos.Y > g_yClientSize)
		m_Cam.m_vCameraPos.Y = -(int)(g_yClientSize / 2);
	else
		m_Cam.m_vCameraPos.Y = -hero.m_vPos.Y + g_yClientSize / 2;

	hero.Frame();
	m_Cam.Move(hero.m_vOffset);
	m_Cam.Frame();

}
void    MySceneIngame::Render()
{
	objScreen.SetViewTransform(m_Cam.GetMatrix());
	objScreen.Render(MyDevice::m_pContext);

	m_UIList[0].PreRender(MyDevice::m_pContext);
	MyDevice::m_pContext->PSSetShaderResources(0, 1,
		m_UIList[0].m_pSprite->GetSRV(m_iNpcCounter).GetAddressOf());
	m_UIList[0].PostRender(MyDevice::m_pContext);

	//for (auto obj : m_UIList)
	for (int iUI = 1; iUI < m_UIList.size(); iUI++)
	{
		m_UIList[iUI].UpdateSprite();
		// 화면 고정( 뷰 변환 생략 )
		//obj.SetViewTransform(m_Cam.GetMatrix());
		m_UIList[iUI].Render(MyDevice::m_pContext);
	}

	/// <summary>
	/// 
	/// </summary>
	hero.SetViewTransform(m_Cam.GetMatrix());

	if (I_Input.KeyCheck('D') == KEY_PUSH)
	{
		hero.SetAnim(0.5f, I_Sprite.GetPtr(L"Antonio"));
	}
	else if (I_Input.KeyCheck('A') == KEY_PUSH)
	{
		hero.SetAnim(0.5f, I_Sprite.GetPtr(L"AntonioReversed"));
	}

	if(hero.bIsMove)
		hero.UpdateSprite();

	hero.Render(MyDevice::m_pContext);
	
	bool bGameEnding = true;

	for_each(begin(m_npcList), end(m_npcList), [&](auto& obj)
		{
			if (!obj.m_bDead)
			{
				obj.UpdateSprite();
				obj.SetViewTransform(m_Cam.GetMatrix());
				obj.Render(MyDevice::m_pContext);
				bGameEnding = false;
			}
		});

	// 적 격퇴
	if (bGameEnding)
	{
		m_iLevel++;
		LevelUp(m_iLevel);
	}
}
void    MySceneIngame::Release()
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

