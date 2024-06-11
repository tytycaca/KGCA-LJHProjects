////////////////////////////////////////////////////
// Sample ���� �׽�Ʈ�� �Ϸ��ϰ� MyCore�� �����Ѵ�. //
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
	// ������ ��Ģ!! ������ 4���� �Լ��� � ����� �����ϵ� �ݵ�� �����Ǿ� �־���Ѵ�!
	// (�����ϱ� ���� ���������Լ��� �����δ� �͵� ����)
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

