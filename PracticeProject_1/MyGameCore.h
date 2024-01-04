#pragma once
#include "MyDevice.h"
#include "MyTimer.h"
#include "MyDxWrite.h"
#include "MyInput.h"
#include "MyPlaneShape.h"

class MyGameCore : public MyDevice
{
// 모듈 객체 생성
public:
	MyTimer m_MyTimer;

// 샘플링 및 블랜딩
public:
	ID3D11SamplerState* m_pDefaultSS = nullptr;
	ID3D11SamplerState* m_pDefaultSSPoint = nullptr;
	ID3D11BlendState* m_pAlphaBlendEnable = nullptr;
	ID3D11BlendState* m_pAlphaBlendDisable = nullptr;
	ID3D11BlendState* m_pDualSourceColorBlending = nullptr;

public:
	// 배경
	std::shared_ptr<MyPlaneShape> m_BackgroundPlane;
	// 오렌지색 박스 배경
	std::shared_ptr<MyPlaneShape> m_BoxPlane;
	// 박스 왼쪽 바
	std::shared_ptr<MyPlaneShape> m_LeftBarPlane;
	// 박스 오른쪽 바
	std::shared_ptr<MyPlaneShape> m_RightBarPlane;
	// 박스 바닥 바
	std::shared_ptr<MyPlaneShape> m_BottomBarPlane;
	// 타이틀
	std::shared_ptr<MyPlaneShape> m_TitlePlane;
	// 과일 레벨
	std::shared_ptr<MyPlaneShape> m_FruitLevelPlane;

// GameCore 의 기능을 수행할 함수 정의
public:
	bool	DualSourceColorBlending();
	bool    AlphaBlendState();
	bool	CreateSampleState();

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

