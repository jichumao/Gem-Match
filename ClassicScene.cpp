#pragma once
#include "ClassicScene.h"
#include "ResLoader.h"
#include "resource.h"

bool g_SoundOpen = true;

ClassicScene::ClassicScene()
{
	auto delay = gcnew Delay(1.0f);
	auto opacityBy = gcnew OpacityBy(2.0f, 1.0f);
	auto sequence = gcnew Sequence({ delay, opacityBy });
	// 添加背景
	auto background = gcnew Sprite(ResLoader::getImage(L"ClassicScene"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(background);
	
	//创建按钮显示精灵
	auto start = gcnew Sprite(ResLoader::getImage(L"StartGame"));
	auto start_selected = gcnew Sprite(ResLoader::getImage(L"StartGame"));
	start->setScale(2.0f);
	start_selected->setScale(1.7f);
	start_selected->movePosY((start->getHeight() - start_selected->getHeight()) / 2);
	start_selected->movePosX((start->getWidth() - start_selected->getWidth()) / 2);
	//添加开始按钮
	auto start_btn = gcnew Button(start, start_selected);
	start_btn->setOpacity(0.0f);
	auto sequence_2 = gcnew Sequence({ delay->clone(), sequence->clone() });
	start_btn->runAction(sequence_2->clone());
	//// 按下开始按钮，进入 Game 场景
	//start_btn->setClickFunc([]
	//	{
	//		SceneManager::enter(gcnew PatternScene(), gcnew FadeTransition(0.6f));
	//	});
	//start_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 70);
	//this->addChild(start_btn);


	// 创建声音开关按钮
	soundBtn = gcnew Button(gcnew Sprite(g_SoundOpen ? L"res/soundon.png" : L"res/soundoff.png"));
	// 设置声音开关按钮位置
	soundBtn->setPos(Window::getWidth() - 30, 50);
	// 设置声音开关按钮回调函数
	soundBtn->setClickFunc(std::bind(&ClassicScene::Sound, this));
	this->addChild(soundBtn);

}

void ClassicScene::Sound()
{
	// 获取按钮状态
	if (!g_SoundOpen)
	{
		// 继续背景音乐
		MusicPlayer::resume(L"res\\background.wav");
		soundBtn->setNormal(gcnew Sprite(L"res\\soundon.png"));
		g_SoundOpen = true;
	}
	else
	{
		// 暂停背景音乐
		MusicPlayer::pause(L"res\\background.wav");
		soundBtn->setNormal(gcnew Sprite(L"res\\soundoff.png"));
		g_SoundOpen = false;
	}
	// 保存信息到文件
	Data::saveBool(L"sound", g_SoundOpen);
}