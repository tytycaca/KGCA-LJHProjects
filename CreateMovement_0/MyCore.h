#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWriterFont.h"

// �׽�Ʈ�� �Ϸ��ϰ�  TCore�� �����Ѵ�.
class MyCore : public MyDevice, public MyBaseCore
{
public:
	MyInput m_Input;
	MyTimer m_Timer;
	MyWriterFont  m_font;
public:
	virtual void Init();
	virtual void Frame();
	virtual void Render();
	virtual void Release();
private:
	void   GamePreFrame();
	void   GameFrame();
	void   GamePostFrame();

	void   GamePreRender();
	void   GameRender();
	void   GamePostRender();

	void   DebugRender();

	void   GameInit();	
	void   GameRelease();
public:
	void   GameRun();
};

