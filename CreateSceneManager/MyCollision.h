#pragma once
#include "MyStd.h"
class MyCollision
{
public:
	static bool RectToRect(RECT& rt1, RECT& rt2);
	static bool RectToPt(RECT& rt1, POINT pt);
};

