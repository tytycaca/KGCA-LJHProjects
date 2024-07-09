#include "MySceneResult.h"
#include "MyInput.h"
void   MySceneResult::Init()
{
	m_pBGSound = I_Sound.Load(L"../../resource/Winner SFX.wav");
	m_buttonSound = I_Sound.Load(L"../../resource/sfx_morph.wav");
	/*if (m_pBGSound && m_ssCurrentSceneStatus == SceneStatus::GameOver)
	{
		m_pBGSound->Play(false);
	}*/

	RECT rtBk = { 0, 0, 1280, 720.0f };
	objScreen.Create(MyDevice::m_pd3dDevice.Get(),
		MyDevice::m_pContext, rtBk,
		L"../../resource/SceneStageComplete.png",
		L"intro.txt");
	objScreen.m_pSprite = nullptr;

	m_UIList.resize(1);
	m_UIList[0].Create(MyDevice::m_pd3dDevice.Get(), MyDevice::m_pContext, { 528 , 500, 732, 559 },
		L"../../resource/endgame_normal.png",
		L"intro.txt");
	m_UIList[0].SetAnim(1.0f, I_Sprite.GetPtr(L"EndGameButton"));

}
void    MySceneResult::Frame()
{
	for (auto& ui : m_UIList)
	{
		if (MyCollision::RectToPt(ui.m_rt, I_Input.m_ptMousePos))
		{
			ui.m_usCurrentUIStatus = UIStatus::Hover;

			if (I_Input.KeyCheck(VK_LBUTTON) == KEY_PUSH || I_Input.KeyCheck(VK_LBUTTON) == KEY_HOLD)
			{
				ui.m_usCurrentUIStatus = UIStatus::Pressed;
				m_buttonSound->Play(false);
			}
			if (I_Input.KeyCheck(VK_LBUTTON) == KEY_UP)
			{
				ui.m_usCurrentUIStatus = UIStatus::End;
				m_bStartFadeOut = true;
				m_bFadeOut = true;
			}
		}
		else
			ui.m_usCurrentUIStatus = UIStatus::Default;

		ui.Frame();
	}

	if (m_bStartFadeOut == true)
	{
		static float alpha1 = 0.0f;
		alpha1 += g_fSecondPerFrame * 2.0f;
		for (auto& v : objScreen.m_vList)
		{
			if (m_bFadeOut)
			{
				v.c.X = max(0.0f, 1.0f - alpha1);
				v.c.Y = max(0.0f, 1.0f - alpha1);
				v.c.Z = max(0.0f, 1.0f - alpha1);
				v.c.W = max(0.0f, 1.0f - alpha1);
			}
			else
			{
				v.c.X = 1.0f;
				v.c.Y = 1.0f;
				v.c.Z = 1.0f;
				v.c.W = min(1.0f, alpha1); //fade in
			}
		}
		objScreen.UpdateVertexBuffer();

		if (alpha1 > 2.0f && m_bFadeOut == false)
		{
			m_bFadeOut = true;
			alpha1 = 0.0f;
		}

		if (alpha1 > 2.0f && m_bFadeOut)
		{
			g_bGameRun = false;
		}
	}

	if (m_bStartFadeOut == true)
	{
		static float alpha1 = 0.0f;
		alpha1 += g_fSecondPerFrame * 2.0f;
		for (auto& v : m_UIList[0].m_vList)
		{
			if (m_bFadeOut)
			{
				v.c.X = max(0.0f, 1.0f - alpha1);
				v.c.Y = max(0.0f, 1.0f - alpha1);
				v.c.Z = max(0.0f, 1.0f - alpha1);
				v.c.W = max(0.0f, 1.0f - alpha1);
			}
			else
			{
				v.c.X = 1.0f;
				v.c.Y = 1.0f;
				v.c.Z = 1.0f;
				v.c.W = min(1.0f, alpha1); //fade in
			}
		}
		m_UIList[0].UpdateVertexBuffer();

		if (alpha1 > 2.0f && m_bFadeOut == false)
		{
			m_bFadeOut = true;
			alpha1 = 0.0f;
		}

		if (alpha1 > 2.0f && m_bFadeOut)
		{
			g_bGameRun = false;
		}
	}
}
void    MySceneResult::Render()
{
	objScreen.Render(MyDevice::m_pContext);

	if (m_UIList[0].m_usCurrentUIStatus == UIStatus::Default)
	{
		m_UIList[0].PreRender(MyDevice::m_pContext);
		MyDevice::m_pContext->PSSetShaderResources(0, 1,
			m_UIList[0].m_pSprite->GetSRV(0).GetAddressOf());
		m_UIList[0].PostRender(MyDevice::m_pContext);
	}
	else if (m_UIList[0].m_usCurrentUIStatus == UIStatus::Hover)
	{
		m_UIList[0].PreRender(MyDevice::m_pContext);
		MyDevice::m_pContext->PSSetShaderResources(0, 1,
			m_UIList[0].m_pSprite->GetSRV(1).GetAddressOf());
		m_UIList[0].PostRender(MyDevice::m_pContext);
	}
	else if (m_UIList[0].m_usCurrentUIStatus == UIStatus::Pressed)
	{
		m_UIList[0].PreRender(MyDevice::m_pContext);
		MyDevice::m_pContext->PSSetShaderResources(0, 1,
			m_UIList[0].m_pSprite->GetSRV(2).GetAddressOf());
		m_UIList[0].PostRender(MyDevice::m_pContext);
	}

	//m_WriterFont.get()->RenderText(L"게임 종료", D2D1_RECT_F{ 577, 512, 697, 536 }, D2D1_COLOR_F{1, 1, 1, 1});
}
void    MySceneResult::Release()
{
	objScreen.Release();
	for (auto& obj : m_UIList)
	{
		obj.Release();
	}
}