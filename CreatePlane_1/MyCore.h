////////////////////////////////////////////////////
// Sample 에서 테스트를 완료하고 MyCore에 포함한다. //
///////////////////////////////////////////////////
#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWriterFont.h"

class MyCore : public MyDevice, MyBaseCore
{
public:
	MyInput m_Input;
	MyTimer m_Timer;
	MyWriterFont m_Font;

public:
	// 정해진 규칙!! 이하의 4개의 함수는 어떤 기능을 구현하든 반드시 구현되어 있어야한다!
	// (강제하기 위해 순수가상함수로 만들어두는 것도 좋음)
	virtual void Init() override;
	virtual void Frame() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void GamePreFrame();
	void GameFrame();
	void GamePostFrame();

	void GamePreRender();
	void GamePostRender();
	void GameRender();

	void DebugRender();

	void GameInit();
	void GameRelease();

public:
	void GameRun();
};

