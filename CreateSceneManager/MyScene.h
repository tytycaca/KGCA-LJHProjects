#pragma once
#include "MyHero.h"
#include "MyNpc.h"
#include "MySound.h"
#include "MySprite.h"
#include "MyCamera.h"
class MyScene
{
public:
	bool	m_bSceneChange = false;
	std::shared_ptr<MySound>				m_pBGSound = nullptr;
public:
	virtual void    Init() {};
	virtual void    Frame() {};
	virtual void    Render() {};
	virtual void    Release() {};
};

