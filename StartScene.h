#pragma once
#include "common.h"
//#include <graphics.h>		// 引用图形库头文件
#include <conio.h>

//开始界面
class StartScene
	: public Scene
{
public:
	StartScene();
	void Sound();
protected:
	// 声音开关
	Button* soundBtn;
	// 继续游戏按钮
	Button* resumeBtn;

	bool g_SoundOpen = true;
};

