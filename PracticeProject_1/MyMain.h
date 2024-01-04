#pragma once
#include "MyGameCore.h"
#include "MyPlayerObj.h"

class MyMain : public MyGameCore
{
	std::shared_ptr<MyPlayerObj> m_Player;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

