#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"
// Sample 에서 테스트를 완료하고 MyCore에 포함한다.

class MyBaseCore
{
	virtual void Init() = 0;
	virtual void Frame() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

class MyCore : public MyDevice, MyBaseCore
{
public:
	MyInput m_Input;
	MyTimer m_Timer;

public:
	// 정해진 규칙!! 이하의 4개의 함수는 어떤 기능을 구현하든 반드시 구현되어 있어야한다!
	// (강제하기 위해 순수가상함수로 만들어두는 것도 좋음)
	virtual void Init();
	virtual void Frame();
	virtual void Render();
	virtual void Release();

private:
	void GamePreFrame();
	void GameFrame();
	void GamePostFrame();

	void GamePreRender();
	void GamePostRender();
	void GameRender();

	void DebugRender();

	virtual void GameInit() override;
	virtual void GameRun() override;
	virtual void GameRelease() override;
};

