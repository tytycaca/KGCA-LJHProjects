#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyDxWrite.h"
#include "MyInput.h"
#include "MyPlaneShape.h"

class MyGameCore : public MyDevice
{
// ��� ��ü ����
public:
	MyTimer m_MyTimer;

// ���ø� �� ����
public:
	ID3D11SamplerState* m_pDefaultSS = nullptr;
	ID3D11SamplerState* m_pDefaultSSPoint = nullptr;
	ID3D11BlendState* m_pAlphaBlendEnable = nullptr;
	ID3D11BlendState* m_pAlphaBlendDisable = nullptr;
	ID3D11BlendState* m_pDualSourceColorBlending = nullptr;

public:
	// ���
	std::shared_ptr<MyPlaneShape> m_BackgroundPlane;
	// �������� �ڽ� ���
	std::shared_ptr<MyPlaneShape> m_BoxPlane;
	// �ڽ� ���� ��
	std::shared_ptr<MyPlaneShape> m_LeftBarPlane;
	// �ڽ� ������ ��
	std::shared_ptr<MyPlaneShape> m_RightBarPlane;
	// �ڽ� �ٴ� ��
	std::shared_ptr<MyPlaneShape> m_BottomBarPlane;
	// Ÿ��Ʋ
	std::shared_ptr<MyPlaneShape> m_TitlePlane;
	// ���� ����
	std::shared_ptr<MyPlaneShape> m_FruitLevelPlane;

// GameCore �� ����� ������ �Լ� ����
public:
	bool	DualSourceColorBlending();
	bool    AlphaBlendState();
	bool	CreateSampleState();

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

