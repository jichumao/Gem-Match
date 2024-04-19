#pragma once
#include "SpeedRankScene.h"
#include "StartScene.h"
#include "ResLoader.h"
#include "PatternScene.h"
#include "RankScene.h"
#include <iostream>
#include <windows.h>
Scene* g_Scene_Speed;		// 场景
Node* g_Panel_Speed;		// 关卡面板

using namespace std;

SpeedRankScene::SpeedRankScene()
{

	// 创建背景图对象
	auto background1 = gcnew Sprite(L"res/BG03.png");
	// 背景图居中显示
	background1->setPos(Window::getSize() / 2);
	// 将图片添加到场景中
	this->addChild(background1);


	//设置返回主界面精灵
	auto returnMain = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	auto returnMain_selected = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	returnMain->setScale(1.0f);
	returnMain_selected->setScale(0.8f);
	returnMain_selected->movePosY((returnMain->getHeight() - returnMain_selected->getHeight()) / 2);
	returnMain_selected->movePosX((returnMain_selected->getWidth() - returnMain_selected->getWidth()) / 2);

	//添加返回主菜单按钮
	auto returnMain_btn = gcnew Button(returnMain, returnMain_selected);

	// 按下返回按钮，进入 主菜单 场景
	returnMain_btn->setClickFunc([]
		{
			SceneManager::back();
		});
	returnMain_btn->setPos(Window::getWidth() - 50, Window::getHeight() - 50);

	this->addChild(returnMain_btn);

	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2);
	//// 创建文字
	//auto Text = gcnew Sprite(L"res/LS10.png");
	//Text->setPosY(Window::getHeight() - 300);
	// 图片居中
	Image->setPosX(Window::getWidth() / 2);
	this->addChild(Image);

	//获取排行榜数据
	DataBase db;
	vector<node> list = db.getRank(7);

	// 创建文字样式
	auto style = Text::Style();
	style.color = Color::White;          // 颜色为蓝色
	style.hasOutline = true;            // 开启文字描边
	style.outlineColor = Color::SkyBlue;    // 文字描边颜色
	style.outlineWidth = 2.0;           // 文字描边宽度为 2.0
	style.wrapping = true;              // 开启自动换行
	style.wrappingWidth = 70;           // 文字自动换行的宽度为 70（像素）

	// 创建文字样式2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // 颜色为蓝色
	style2.hasOutline = true;            // 开启文字描边
	style2.outlineColor = Color::Black;    // 文字描边颜色
	style2.outlineWidth = 2.0;           // 文字描边宽度为 2.0
	style2.wrapping = true;              // 开启自动换行
	style2.wrappingWidth = 10;           // 文字自动换行的宽度为 70（像素）

	auto textTopic = gcnew Text(L"竞速模式");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275,300);
	this->addChild(textTopic);
	//打印信息
	for (int i = 0; i < list.size(); i++) {

	string s0 = list[i].name;	
	auto text = gcnew Text(RankScene::String2WString(s0));
	text->setPos(445, 110+ 42*i);
	text->setStyle(style);
	this->addChild(text);

	int i1 = list[i].score;
	string s1 = to_string(i1);
	auto text1 = gcnew Text(RankScene::String2WString(s1));
	text1->setPos(595, 110 + 42 * i);
	this->addChild(text1);
	}
	
}



