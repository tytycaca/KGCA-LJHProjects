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

	m_UIList.resize(9);
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

	m_UIList[4].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 0, 0, 1, 35 },
		L"../../resource/exp_bar.png",
		L"Alphablend.hlsl");

	m_UIList[5].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 0, 0, 1280, 35 },
		L"../../resource/exp_bar_empty.png",
		L"Alphablend.hlsl");

	m_UIList[6].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 0, 0, 1280, 35 },
		L"../../resource/exp_bar_bg.png",
		L"Alphablend.hlsl");

	m_UIList[7].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 615, 390, 665, 395 },
		L"../../resource/hp_bar.png",
		L"Alphablend.hlsl");

	m_UIList[8].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ 664, 390, 665, 395 },
		L"../../resource/hp_bar_bg.png",
		L"Alphablend.hlsl");
}
void   MySceneIngame::SetPlayer()
{
	hero.m_vInitPos.X = 640.0f;
	hero.m_vInitPos.Y = 360.0f;
	hero.m_fWidth = 50.0f;
	hero.m_fHeight = 50.0f;
	hero.Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ (LONG)(hero.m_vInitPos.X - hero.m_fWidth / 2),
		  (LONG)(hero.m_vInitPos.Y - hero.m_fHeight / 2),
		  (LONG)(hero.m_vInitPos.X + hero.m_fWidth / 2),
		  (LONG)(hero.m_vInitPos.Y + hero.m_fHeight / 2)},
		L"../../resource/Antonio_01.png",
		L"Player.hlsl");
	//hero.SetAnim(0.5f, I_Sprite.GetPtr(L"Antonio"));
	hero.m_fSpeed = 300.0f;
}
void   MySceneIngame::SetWeaponWhip()
{
	m_pWeaponWhip->Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
		{ (LONG)(hero.m_vInitPos.X),
		  (LONG)(hero.m_vInitPos.Y - hero.m_fHeight / 2),
		  (LONG)(hero.m_vInitPos.X + hero.m_fWidth * 4),
		  (LONG)(hero.m_vInitPos.Y + hero.m_fHeight / 2) },
		L"../../resource/whipVfx0.png",
		L"Alphablend.hlsl");
	m_pWeaponWhip->SetAnim(m_pWeaponWhip->m_fAnimDuration, I_Sprite.GetPtr(L"WeaponWhip"));
	m_pWeaponWhip->m_fSpeed = 300.0f;
}
void    MySceneIngame::LevelUp(UINT iLevel)
{
	Sleep(100);
	/*std::vector<std::wstring> spriteName =
	{
		L"DefalultNumber",
		L"wik",
		L"rtClash",
		L"IconList",
		L"rtBomb",
		L"rtExplosion",
	};*/

	hero.m_vPos.X = 640.0f;
	hero.m_vPos.Y = 360.0f;
	m_pWeaponWhip->m_vPos.X = 740.0f;
	m_pWeaponWhip->m_vPos.Y = 360.0f;
	m_Cam.m_vCameraPos = { 0.0f,0.0f };
	for (int iNpc = 0; iNpc < iLevel; iNpc++)
	{
		MyNpc npc;
		MY_Math::FVector2 pos;
		pos.X = randstep(-640, 1920);
		pos.Y = randstep(-360, 1080);
		npc.Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext,
			{ (LONG)pos.X, (LONG)pos.Y,(LONG)(pos.X + 30.0f), (LONG)(pos.Y + 30.0f) },
			L"../../resource/Bat1_0.png",
			L"Alphablend.hlsl");

		/*npc.SetAnim(1.0f, I_Sprite.GetPtr(spriteName[m_iLevel % spriteName.size()]));*/
		npc.SetAnim(1.0f, I_Sprite.GetPtr(L"MonsterBat"));
		m_npcList.push_back(npc);
	}
	m_iNpcCounter = m_npcList.size();
	m_pWeaponWhip->m_fCooltimeCounter = 0.0f;
}
void   MySceneIngame::Init()
{
	SetSound();
	SetUI();
	SetPlayer();
	SetWeaponWhip();
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

	objScreen.Frame();

	for (auto& ui : m_UIList)
	{
		ui.Frame();
	}

	hero.m_fHitTimer += g_fSecondPerFrame;

	for (auto& npc : m_npcList)
	{
		npc.Frame();
		if (npc.m_bDead == false
			&& MyCollision::RectToRect(npc.m_rt, m_pWeaponWhip->m_rt)
			&& m_pWeaponWhip->m_bAnimOn)
		{
			npc.m_bIsHit = true;
			npc.m_bIsDmged = true;
			npc.m_bDead = true;
			hero.m_fEXP += 30;
			m_iNpcCounter = max(0, m_iNpcCounter - 1);
		}
		else
		{
			npc.m_bIsHit = false;
			npc.m_bIsDmged = false;
		}
		
		if (MyCollision::RectToRect(hero.m_rt, npc.m_rt))
		{
			if (!npc.m_bDead)
			{
				hero.m_bIsHit = true;
				npc.m_bIsHit = true;

				if (hero.m_fHitTimer >= hero.m_fHitCooltime)
				{
					hero.m_bIsDmged = true;
					hero.m_fHP -= 10.0f;
					if (hero.m_fHP <= 0.0f)
						g_bGameRun = false;
					hero.m_fHitTimer = 0.0f;
				}
				else
				{
					hero.m_bIsDmged = false;
				}
			}
		}
		else
		{
			hero.m_bIsHit = false;
			npc.m_bIsHit = false;
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

	if (I_Input.KeyCheck('D') == KEY_PUSH)
	{
		hero.m_bIsRight = true;
		m_pWeaponWhip->SetAnim(m_pWeaponWhip->m_fAnimDuration, I_Sprite.GetPtr(L"WeaponWhip"));
		hero.SetAnim(0.5f, I_Sprite.GetPtr(L"Antonio"));
	}
	else if (I_Input.KeyCheck('A') == KEY_PUSH)
	{
		hero.m_bIsRight = false;
		m_pWeaponWhip->SetAnim(m_pWeaponWhip->m_fAnimDuration, I_Sprite.GetPtr(L"WeaponWhipReversed"));
		hero.SetAnim(0.5f, I_Sprite.GetPtr(L"AntonioReversed"));
	}

	if (I_Input.KeyCheck('A') == KEY_HOLD)
	{
		hero.m_bIsMove = true;
		if (hero.m_vPos.X - 25 > objScreen.m_rt.left)
		{
			hero.Move({ -1.0f,0.0f });
			m_pWeaponWhip->Move({ -1.0f,0.0f });
			m_UIList[7].Move({ -1.0f,0.0f });
			m_UIList[8].Move({ -1.0f,0.0f });
		}
	}
	if (I_Input.KeyCheck('D') == KEY_HOLD)
	{
		hero.m_bIsMove = true;
		if (hero.m_vPos.X + 25 < objScreen.m_rt.right)
		{
			hero.Move({ 1.0f,0.0f });
			m_pWeaponWhip->Move({ 1.0f,0.0f });
			m_UIList[7].Move({ 1.0f,0.0f });
			m_UIList[8].Move({ 1.0f,0.0f });
		}
	}
	if (I_Input.KeyCheck('W') == KEY_HOLD)
	{
		hero.m_bIsMove = true;
		if (hero.m_vPos.Y - 25 > objScreen.m_rt.top + 375)
		{
			hero.Move({ 0.0f,-1.0f });
			m_pWeaponWhip->Move({ 0.0f,-1.0f });
			m_UIList[7].Move({ 0.0f,-1.0f });
			m_UIList[8].Move({ 0.0f,-1.0f });
		}
	}
	if (I_Input.KeyCheck('S') == KEY_HOLD)
	{
		hero.m_bIsMove = true;
		if (hero.m_vPos.Y + 25 < objScreen.m_rt.bottom - 375)
		{
			hero.Move({ 0.0f,1.0f });
			m_pWeaponWhip->Move({ 0.0f,1.0f });
			m_UIList[7].Move({ 0.0f,1.0f });
			m_UIList[8].Move({ 0.0f,1.0f });
		}
	}

	if (I_Input.KeyCheck('W') == KEY_UP)
		hero.m_bIsMove = false;
	if (I_Input.KeyCheck('S') == KEY_UP)
		hero.m_bIsMove = false;
	if (I_Input.KeyCheck('A') == KEY_UP)
		hero.m_bIsMove = false;
	if (I_Input.KeyCheck('D') == KEY_UP)
		hero.m_bIsMove = false;

	if (hero.m_vPos.X < 0)
		m_Cam.m_vCameraPos.X = g_xClientSize / 2;
	else if (hero.m_vPos.X > g_xClientSize)
		m_Cam.m_vCameraPos.X = -(float)(g_xClientSize / 2);
	else
		m_Cam.m_vCameraPos.X = -hero.m_vPos.X + g_xClientSize / 2;

	if (hero.m_vPos.Y < 0)
		m_Cam.m_vCameraPos.Y = g_yClientSize / 2;
	else if (hero.m_vPos.Y > g_yClientSize)
		m_Cam.m_vCameraPos.Y = -(float)(g_yClientSize / 2);
	else
		m_Cam.m_vCameraPos.Y = -hero.m_vPos.Y + g_yClientSize / 2;

	if (hero.m_bIsRight)
	{
		MY_Math::FVector2 p = MY_Math::FVector2(hero.m_vPos.X + 100.0f, hero.m_vPos.Y);
		m_pWeaponWhip->SetPos(p);
	}
	else
	{
		MY_Math::FVector2 p = MY_Math::FVector2(hero.m_vPos.X - 100.0f, hero.m_vPos.Y);
		m_pWeaponWhip->SetPos(p);
	}

	//MY_Math::FVector2 p = MY_Math::FVector2(hero.m_vPos.X, hero.m_vPos.Y +32.5f);
	//m_UIList[7].SetPos(p); // hp 바 게이지
	//p = MY_Math::FVector2(hero.m_vPos.X + 25.0f, hero.m_vPos.Y + 32.5f);
	//m_UIList[8].SetPos(p); // hp 바 배경
	m_UIList[7].Frame();
	m_UIList[8].Frame();

	hero.Frame();
	m_pWeaponWhip->Frame();
	m_Cam.Move(hero.m_vOffset);
	m_Cam.Frame();

}
void    MySceneIngame::Render()
{
	objScreen.SetViewTransform(m_Cam.GetMatrix());
	objScreen.Render(MyDevice::m_pContext);

	//m_UIList[0].PreRender(MyDevice::m_pContext);
	//MyDevice::m_pContext->PSSetShaderResources(0, 1,
	//	m_UIList[0].m_pSprite->GetSRV(m_iNpcCounter).GetAddressOf());
	//m_UIList[0].PostRender(MyDevice::m_pContext);

	////for (auto obj : m_UIList)
	//for (int iUI = 1; iUI < m_UIList.size()-2; iUI++)
	//{
	//	m_UIList[iUI].UpdateSprite();
	//	// 화면 고정( 뷰 변환 생략 )
	//	//obj.SetViewTransform(m_Cam.GetMatrix());
	//	m_UIList[iUI].Render(MyDevice::m_pContext);
	//}

	m_UIList[6].Render(MyDevice::m_pContext); // EXP바 배경
	m_UIList[4].PreRender(MyDevice::m_pContext); // EXP바 게이지
	MY_Math::FVector2 scale = MY_Math::FVector2(g_xClientSize * hero.m_fEXP / 50, 1);
	m_UIList[4].SetScale(scale);
	m_UIList[4].UpdateVertexBuffer();
	m_UIList[4].PostRender(MyDevice::m_pContext);
	m_UIList[5].Render(MyDevice::m_pContext); // EXP바 테두리

	m_UIList[7].SetViewTransform(m_Cam.GetMatrix());
	m_UIList[8].SetViewTransform(m_Cam.GetMatrix());
	m_UIList[7].Render(MyDevice::m_pContext); // EXP바 게이지
	//m_UIList[8].PreRender(MyDevice::m_pContext); // EXP바 배경
	//scale = MY_Math::FVector2(50 * (100-hero.m_fHP) / 100, 1);
	//m_UIList[8].SetScale(scale);
	//MY_Math::FVector2 trans = MY_Math::FVector2(-(50 * (100 - hero.m_fHP) / 200), 0);
	//m_UIList[8].SetTrans(trans);
	//m_UIList[8].UpdateVertexBuffer();
	//m_UIList[8].PostRender(MyDevice::m_pContext);
	
	m_WriterFont.get()->RenderLevel(hero.m_iCharLv, D2D1_RECT_F{ 1200, 4, 1280, 26 }, D2D1_COLOR_F{ 1, 1, 1, 1 });
	m_WriterFont.get()->RenderHP(hero.m_fHP, D2D1_RECT_F{ 1200, 32, 1280, 56 }, D2D1_COLOR_F{ 1,0,0,1 });
	
	hero.SetViewTransform(m_Cam.GetMatrix());
	for (auto& v : hero.m_vList)
	{
		if (hero.m_bIsHit)
		{
			v.c.X = 1000.0f;
			v.c.Y = 0.1f;
			v.c.Z = 0.1f;
		}
		else
		{
			v.c.X = 1.0f;
			v.c.Y = 1.0f;
			v.c.Z = 1.0f;
		}
	}
	if (hero.m_bIsMove)
		hero.UpdateSprite();
	hero.UpdateVertexBuffer();
	hero.Render(MyDevice::m_pContext);

	m_pWeaponWhip->m_fCooltimeCounter += g_fSecondPerFrame;
	if (m_pWeaponWhip->m_fCooltimeCounter >= m_pWeaponWhip->m_fCooltime)
	{
		m_pWeaponWhip->m_bAnimOn = true;
		m_pWeaponWhip->SetViewTransform(m_Cam.GetMatrix());
		m_pWeaponWhip->UpdateSprite();
		m_pWeaponWhip->Render(MyDevice::m_pContext);

		if (m_pWeaponWhip->GetSpriteIndex() == 5)
		{
			m_pWeaponWhip->m_bAnimOn = false;
			m_pWeaponWhip->SetSpriteIndex(0);
			m_pWeaponWhip->m_fCooltimeCounter = 0.0f;
		}
	}
	
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

