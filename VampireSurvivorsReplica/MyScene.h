#pragma once
#include "MyHero.h"
#include "MyWeaponWhip.h"
#include "MyNpc.h"
#include "MySound.h"
#include "MySprite.h"
#include "MyCamera.h"
#include "MyWriterFont.h"

enum class SceneStatus
{
	Default,
	Title,
	Lobby,
	Ingame,
	Result,
};

class MyScene
{
public:
	bool	m_bSceneChange = false;
	std::shared_ptr<MySound>				m_pBGSound = nullptr;
	SceneStatus m_ssCurrentSceneStatus = SceneStatus::Default;
	std::shared_ptr<MyWriterFont> m_WriterFont;

public:
	virtual void    InitInstance(MyWriterFont mf);
	virtual void    Init() {};
	virtual void    Frame() {};
	virtual void    Render() {};
	virtual void    Release() {};
};

