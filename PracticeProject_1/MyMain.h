#pragma once
#include "MyGameCore.h"

class MyMain : public MyGameCore
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

