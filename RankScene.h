#pragma once

#include <easy2d/easy2d.h>
#include "common.h"

class RankScene :
	public Scene
{
public:
	RankScene();
	static std::wstring String2WString(const std::string& s);
};

