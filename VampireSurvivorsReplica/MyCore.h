#pragma once
#include "MyWindow.h"
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWriterFont.h"
#include "MyTexMgr.h"
#include "MyShaderMgr.h"
#include "MySound.h"
#include "MySprite.h"
// 테스트를 완료하고  TCore에 포함한다.
class MyCore : public MyWindow, public MyBaseCore
{
public:
	MyTimer m_Timer;
	MyWriterFont  m_font;
	

	ComPtr<ID3D11BlendState> m_pAlphaBlend = nullptr;
public:
	virtual void Init();
	virtual void Frame();
	virtual void Render();
	virtual void Release();

	HRESULT  SetAlphaBlendState();
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

