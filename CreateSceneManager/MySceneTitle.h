#pragma once
#include "MyScene.h"
class MySceneTitle : public MyScene
{
	MyActor				objScreen; // »ï°¢Çü
	bool				m_bFadeOut = false;
	std::vector<MyActor> m_UIList;
public:
	virtual void    Init() override;
	virtual void    Frame() override;
	virtual void    Render() override;
	virtual void    Release() override;
};

