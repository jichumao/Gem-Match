#pragma once
#include "common.h"

//开始界面
class ClassicScene
	: public Scene
{
public:
	ClassicScene();
	void Sound();
protected:
	// 声音开关
	Button* soundBtn;
	// 继续游戏按钮
	Button* resumeBtn;

	bool g_SoundOpen = true;
};

