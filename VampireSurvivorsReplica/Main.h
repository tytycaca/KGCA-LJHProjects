#pragma once
#include "MyCore.h"
#include "MySceneTitle.h"
#include "MySceneLobby.h"
#include "MySceneIngame.h"
#include "MySceneResult.h"

class Main : public MyCore
{
	MyScene*		m_pCurrentScene = nullptr;
	std::shared_ptr<MyScene>		m_pTitleScene = nullptr;
	std::shared_ptr<MyScene>		m_pLobbyScene = nullptr;
	std::shared_ptr<MyScene>		m_pIngameScene = nullptr;
	std::shared_ptr<MyScene>		m_pResultScene = nullptr;
public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;
};