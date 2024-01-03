#pragma once
#include "MyDevice.h"
#include "MyTextureMgr.h" // test
#include "MyTimer.h" // test

class MyGameCore : public MyDevice
{
// ��� ��ü ����
public:
	MyTexture m_MyTexture; // test
	MyTimer m_MyTimer; // test

// GameCore �� ����� ������ �Լ� ����
public:



// MyWindow �κ��� ��ӹ޾� �������� �Լ�
public:
	virtual bool	GameInit()	  override;
	virtual bool	GameFrame()   override;
	virtual bool	GameRender()  override;
	virtual bool	GameRelease() override;

// ���� Ŭ�������� �������� �Լ�
public:
	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
};

