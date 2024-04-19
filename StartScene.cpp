#pragma once
#include "StartScene.h"
#include "ResLoader.h"
#include "PatternScene.h"
#include "RankScene.h"
#include <iostream>
#include "mysetting.h"

StartScene::StartScene()
{
	auto delay = gcnew Delay(1.0f);
	auto opacityBy = gcnew OpacityBy(2.0f, 1.0f);
	auto sequence = gcnew Sequence({ delay, opacityBy });
	// 添加背景
	auto background = gcnew Sprite(ResLoader::getImage(L"StartScene"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(background);
	//添加游戏标题
	auto topic = gcnew Sprite(ResLoader::getImage(L"MainTopic"));
	topic->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 170);
	this->addChild(topic);
	topic->setOpacity(0.0f);
	topic->runAction(sequence->clone());
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

	//AllocConsole();
	//freopen("CONOUT$", "w+t", stdout);
	//freopen("CONIN$", "r+t", stdin);
	//FreeConsole();

	// 按下开始按钮，进入 Game 场景
	start_btn->setClickFunc([]
		{
			SceneManager::enter(gcnew PatternScene(), gcnew FadeTransition(0.6f));
		});
	start_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 70);
	this->addChild(start_btn);


	//创建按钮显示精灵
	auto rank = gcnew Sprite(ResLoader::getImage(L"RankBtn"));
	auto rank_selected = gcnew Sprite(ResLoader::getImage(L"RankBtn"));
	rank->setScale(0.8f);
	rank_selected->setScale(0.5f);
	rank_selected->movePosY((rank->getHeight() - rank_selected->getHeight()) / 2);
	rank_selected->movePosX((rank->getWidth() - rank_selected->getWidth()) / 2);
	//添加开始按钮
	auto rankBtn = gcnew Button(rank, rank_selected);
	rankBtn->setOpacity(0.0f);

	rankBtn->runAction(sequence_2->clone());
	rankBtn->setPos(Window::getWidth() -150, Window::getHeight()-50);
	rankBtn->setClickFunc([]
		{
			
			SceneManager::enter(gcnew RankScene(), gcnew FadeTransition(0.6f));
			/*mySetting* m = new mySetting();

			m->show();*/
		});
	
	this->addChild(rankBtn);


	//创建按钮显示精灵
	auto set = gcnew Sprite(ResLoader::getImage(L"SetBtn"));
	auto set_selected = gcnew Sprite(ResLoader::getImage(L"SetBtn"));
	set->setScale(0.7f);
	set_selected->setScale(0.5f);
	set_selected->movePosY((set->getHeight() - set_selected->getHeight()) / 2);
	set_selected->movePosX((set->getWidth() - set_selected->getWidth()) / 2);
	//添加设置按钮
	auto setBtn = gcnew Button(set, set_selected);
	setBtn->setOpacity(0.0f);
	setBtn->runAction(sequence_2->clone());
	setBtn->setPos(Window::getWidth() - 50, Window::getHeight() - 50);
	setBtn->setClickFunc([]
		{	
			mySetting* m = new mySetting();
			m->show();
		});

	this->addChild(setBtn);

	// 创建声音开关按钮
	soundBtn = gcnew Button(gcnew Sprite(g_SoundOpen ? L"res/soundon.png" : L"res/soundoff.png"));
	// 设置声音开关按钮位置
	soundBtn->setPos(Window::getWidth() - 80 ,50);
	// 设置声音开关按钮回调函数
	soundBtn->setClickFunc(std::bind(&StartScene::Sound, this));
	this->addChild(soundBtn);

}

void StartScene::Sound()
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