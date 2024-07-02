#pragma once
#include "MyScene.h"
class MySceneTitle : public MyScene
{
	MyActor				objScreen; // »ï°¢Çü
	MyActor				startbutton_normal;
	MyActor				startbutton_mouseover;
	MyActor				startbutton_pressed;
	bool				m_bFadeOut = false;
	bool				m_bStartFadeOut = false;
	std::vector<MyActor> m_UIList;
public:
	virtual void    Init() override;
	virtual void    Frame() override;
	virtual void    Render() override;
	virtual void    Release() override;
};

