#pragma once
#include "MyCore.h"
#include "MyHero.h"
#include "MyNpc.h"

class MyCamera
{
public:
	MY_Math::FMatrix     m_matCamera;
	MY_Math::FVector2    m_vCameraPos;

	void Frame()
	{
		m_matCamera.Translation(m_vCameraPos);
	}

	MY_Math::FMatrix& GetMatrix()
	{
		return m_matCamera;
	}

	void  SetTransform(MY_Math::FVector2   pos)
	{
		m_matCamera.Translation(pos);
	}

	void Up()
	{
		MY_Math::FVector2 vCamDirection = { 0.0f, 1.0f };
		m_vCameraPos = m_vCameraPos + vCamDirection * 100.0f * g_fSecondPerFrame;
	}

	void Down()
	{
		MY_Math::FVector2 vCamDirection = { 0.0f, -1.0f };
		m_vCameraPos = m_vCameraPos + vCamDirection * 100.0f * g_fSecondPerFrame;
	}

	void Right(float fValue)
	{
		m_vCameraPos.X = m_vCameraPos.X + fValue;
	}

	void Left(float fValue)
	{
		m_vCameraPos.X = m_vCameraPos.X + fValue;
	}
};

class Sample : public MyCore
{
	MyCamera m_Cam;
	MyActor objScreen; // »ï°¢Çü
	std::vector<MyActor> m_UIList;
	std::vector<MyNpc> m_npcList;
	MyHero hero;
	UINT m_iNpcCounter = 0;
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pNumber;

	ComPtr<ID3D11BlendState> m_pAlphaBlend = nullptr;
	HRESULT SetAlphaBlendState();

public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;

};