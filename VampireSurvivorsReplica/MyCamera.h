#pragma once
#include "MyStd.h"
class TCamera
{
public:
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
		m_vCameraPos = m_vCameraPos + vCamDirection * 15.0f * g_fSecondPerFrame;
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

