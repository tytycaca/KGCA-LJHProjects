#include "Main.h"

void   Main::Init()
{
	m_pTitleScene = std::make_shared<MySceneTitle>();
	m_pLobbyScene = std::make_shared<MySceneLobby>();
	m_pIngameScene = std::make_shared<MySceneIngame>();
	m_pResultScene = std::make_shared<MySceneResult>();
	m_pGameOverScene = std::make_shared<MySceneResult>();

	m_pTitleScene->Init();
	m_pLobbyScene->Init();
	m_pIngameScene->Init();
	m_pIngameScene->InitInstance(m_font);
	m_pResultScene->Init();
	m_pGameOverScene->Init();

	m_pCurrentScene = m_pTitleScene.get();

	
}

void    Main::Frame()
{	
	if (m_pCurrentScene->m_bSceneChange)
	{
		if (m_pCurrentScene->m_ssCurrentSceneStatus == SceneStatus::Title)
			m_pCurrentScene = m_pTitleScene.get();
		else if (m_pCurrentScene->m_ssCurrentSceneStatus == SceneStatus::Lobby)
			m_pCurrentScene = m_pLobbyScene.get();
		else if (m_pCurrentScene->m_ssCurrentSceneStatus == SceneStatus::Ingame)
			m_pCurrentScene = m_pIngameScene.get();
		else if (m_pCurrentScene->m_ssCurrentSceneStatus == SceneStatus::Result)
			m_pCurrentScene = m_pResultScene.get();
		else if (m_pCurrentScene->m_ssCurrentSceneStatus == SceneStatus::Result)
			m_pCurrentScene = m_pGameOverScene.get();

		m_pCurrentScene->m_bSceneChange = false;
		m_pCurrentScene->m_pBGSound->Play(true);
	}
	m_pCurrentScene->Frame();
}
void    Main::Render()
{ 		
	m_pCurrentScene->Render();
}
void    Main::Release()
{			
	m_pCurrentScene->Release();
}

T_GAME_START(1280, 720);