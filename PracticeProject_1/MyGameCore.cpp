#include "MyGameCore.h"

bool MyGameCore::GameInit()
{
	CreateDevice();

	m_MyTimer.Init();
	
	Init();

	return true;
}

bool MyGameCore::GameFrame()
{
	m_MyTimer.Frame();

	Frame();

	return true;
}

bool MyGameCore::GameRender()
{
	Render();

	m_MyTimer.Render();

	return true;
}

bool MyGameCore::GameRelease()
{
	m_MyTexture.Release();
	m_MyTimer.Release();

	Release();

	DeleteDevice();

	return true;
}
