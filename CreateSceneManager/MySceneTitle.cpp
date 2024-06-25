#include "MySceneTitle.h"
#include "MyInput.h"
void   MySceneTitle::Init()
{
	m_pBGSound = I_Sound.Load(L"../../data/sound/abel_leaf.asf");
	if (m_pBGSound)
	{
		m_pBGSound->Play(true);
	}

	RECT rtBk = { 0, 0, 800.0f, 600.0f };
	objScreen.Create(MyDevice::m_pd3dDevice.Get(), 
		MyDevice::m_pContext, rtBk,
		L"../../data/title.png",
		L"intro.txt");
	objScreen.m_pSprite = nullptr;

	MyActor button;
	button.Create(MyDevice::m_pd3dDevice.Get(),
		MyDevice::m_pContext, { 280, 370, 520, 430 },
		L"../../data/ui/Zosma/Stage/Gameplay.png",
		L"Alphablend.hlsl");
	//button.SetAnim(1.0f, nullptr);
	m_UIList.push_back(button);
}
void    MySceneTitle::Frame()
{
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

	static float alpha = 0.0f;
	alpha += g_fSecondPerFrame*0.33f;
	for (auto& v : objScreen.m_vList)
	{
		if (m_bFadeOut)
		{
			v.c.X = max(0.0f, 1.0f - alpha);
			v.c.Y = max(0.0f, 1.0f - alpha);
			v.c.Z = max(0.0f, 1.0f - alpha);
			v.c.W = max(0.0f, 1.0f - alpha);
		}
		else
		{
			v.c.X = 1.0f;
			v.c.Y = 1.0f;
			v.c.Z = 1.0f;
			v.c.W = min(1.0f, alpha); //fade in
		}
	}
	objScreen.UpdateVertexBuffer();

	if (alpha > 2.0f && m_bFadeOut ==false)
	{
		m_bFadeOut = true;
		alpha = 0.0f;
	}

	if (alpha > 2.0f && m_bFadeOut)
	{
		m_bSceneChange = true;
		m_pBGSound->Stop();
	}
}
void    MySceneTitle::Render()
{
	//objScreen.SetViewTransform(m_Cam.GetMatrix());
	objScreen.Render(MyDevice::m_pContext);

	m_UIList[0].PreRender(MyDevice::m_pContext);
	/*MyDevice::m_pContext->PSSetShaderResources(0, 1,
		m_UIList[0].m_pSprite->GetSRV(m_iNpcCounter).GetAddressOf());*/
	m_UIList[0].PostRender(MyDevice::m_pContext);
}
void    MySceneTitle::Release()
{
	objScreen.Release();
	for (auto& obj : m_UIList)
	{
		obj.Release();
	}
}