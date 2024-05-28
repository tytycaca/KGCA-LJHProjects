#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"
// Sample ���� �׽�Ʈ�� �Ϸ��ϰ� MyCore�� �����Ѵ�.

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
	// ������ ��Ģ!! ������ 4���� �Լ��� � ����� �����ϵ� �ݵ�� �����Ǿ� �־���Ѵ�!
	// (�����ϱ� ���� ���������Լ��� �����δ� �͵� ����)
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

