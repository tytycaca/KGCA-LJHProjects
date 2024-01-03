#pragma once
#include "MyDevice.h"
#include "MyTextureMgr.h" // test
#include "MyTimer.h" // test

class MyGameCore : public MyDevice
{
// 모듈 객체 생성
public:
	MyTexture m_MyTexture; // test
	MyTimer m_MyTimer; // test

// GameCore 의 기능을 수행할 함수 정의
public:



// MyWindow 로부터 상속받아 재정의한 함수
public:
	virtual bool	GameInit()	  override;
	virtual bool	GameFrame()   override;
	virtual bool	GameRender()  override;
	virtual bool	GameRelease() override;

// 하위 클래스에서 재정의할 함수
public:
	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
};

