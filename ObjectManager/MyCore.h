#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWriterFont.h"
#include "MyTexMgr.h"
#include "MyShaderMgr.h"

// 테스트를 완료하고  TCore에 포함한다.
class MyCore : public MyDevice, public MyBaseCore
{
public:
	MyInput m_Input;
	MyTimer m_Timer;
	MyWriterFont  m_font;
	bool m_bGameRun = true;
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

