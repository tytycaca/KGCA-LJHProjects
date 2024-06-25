#include "Sample.h"

void   Sample::Init()
{
	m_pTitleScene = std::make_shared<MySceneTitle>();
	m_pLobbyScene = std::make_shared<MySceneLobby>();
	m_pIngameScene = std::make_shared<MySceneIngame>();
	m_pResultScene = std::make_shared<MySceneResult>();

	m_pTitleScene->Init();
	m_pLobbyScene->Init();
	m_pIngameScene->Init();
	m_pResultScene->Init();

	m_pCurrentScene = m_pTitleScene.get();

	
}

void    Sample::Frame()
{	
	if (m_pCurrentScene->m_bSceneChange)
	{
		m_pCurrentScene = m_pIngameScene.get();
		m_pCurrentScene->m_bSceneChange = false;
		m_pCurrentScene->m_pBGSound->Play(true);
	}
	m_pCurrentScene->Frame();
}
void    Sample::Render() 
{ 		
	m_pCurrentScene->Render();
}
void    Sample::Release() 
{			
	m_pCurrentScene->Release();
}

T_GAME_START(800, 600);