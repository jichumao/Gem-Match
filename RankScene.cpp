#pragma once
#include "StartScene.h"
#include "ResLoader.h"
#include "PatternScene.h"
#include "RankScene.h"
#include <iostream>
#include "SpeedRankScene.h"
//---------------------------------------------------------
// 函数声明
//---------------------------------------------------------

void InitSpeed();
void InitRound1();
void InitRound2();
void InitRound3();
void InitRound4();
void InitRound5();
void InitRound6();
void InitButton();		// 加载按钮
void MovePanel();		// 移动关卡面板
void ClickLeft();		// 点击左按钮
void ClickRight();		// 点击右按钮

//---------------------------------------------------------
// 全局变量声明
//---------------------------------------------------------

Scene* g_Scene;		// 场景
Node* g_Panel;		// 关卡面板
int		g_Level;		// 当前选中的关卡数
Button* g_LeftButton;	// 左按钮
Button* g_RightButton;	// 右按钮
DataBase db;
//---------------------------------------------------------
// 函数定义
//---------------------------------------------------------

std::wstring RankScene::String2WString(const std::string& s)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const char* chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[]wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return wstrResult;
}

RankScene::RankScene()
{
	auto background = gcnew Sprite(L"res/StartScene.png");
	background->setPos(Window::getSize() / 2);
	this->addChild(background);

	// 创建一个空场景
	g_Scene = new Scene();
	// 设置当前关卡为 0
	g_Level = 0;

	// 创建背景图对象
	auto background1 = gcnew Sprite(L"res/BG03.png");
	// 背景图居中显示
	background1->setPos(Window::getSize() / 2);
	// 将图片添加到场景中
	g_Scene->addChild(background1);

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
			SceneManager::enter(gcnew StartScene());
		});
	returnMain_btn->setPos(Window::getWidth() - 50, Window::getHeight() - 50);
	this->addChild(returnMain_btn);

	//设置返回主界面精灵
	auto returnMain1 = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	auto returnMain_selected1 = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	returnMain1->setScale(1.0f);
	returnMain_selected1->setScale(0.8f);
	returnMain_selected1->movePosY((returnMain1->getHeight() - returnMain_selected1->getHeight()) / 2);
	returnMain_selected1->movePosX((returnMain_selected1->getWidth() - returnMain_selected1->getWidth()) / 2);

	//添加返回主菜单按钮
	auto returnMain_btn1 = gcnew Button(returnMain1, returnMain_selected1);
	returnMain_btn1->setClickFunc([]
		{
			SceneManager::back();
		});

	returnMain_btn1->setPos(Window::getWidth() - 50, Window::getHeight() - 50);
	g_Scene->addChild(returnMain_btn1);


	// 三个关卡图片合并为 panel 节点
	g_Panel = gcnew Node();
	g_Scene->addChild(g_Panel);

	// 加载关卡图片
	
	InitRound1();
	InitRound2();
	InitRound3();
	InitRound4();
	InitRound5();
	InitRound6();

	// 添加按钮
	InitButton();

	//添加进入经典模式按钮
	auto start = gcnew Sprite(ResLoader::getImage(L"StartGame"));
	auto start_btn = gcnew Button(start);

	start_btn->setClickFunc([]
		{
			SceneManager::enter(g_Scene, gcnew FadeTransition(0.6f));
		});

	start_btn->setPos(Window::getWidth() / 2 - 100, Window::getHeight() / 2 - 100);
	this->addChild(start_btn);
	
	//添加进入竞速模式按钮
	auto speed = gcnew Sprite(ResLoader::getImage(L"StartGame"));
	auto speed_btn = gcnew Button(speed);

	speed_btn->setClickFunc([]
		{
			SceneManager::enter(gcnew SpeedRankScene(), gcnew FadeTransition(0.6f));
		});

	speed_btn->setPos(Window::getWidth() / 2 + 100, Window::getHeight() / 2 + 100);
	this->addChild(speed_btn);
}




void InitRound1()
{
	// 创建图片
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );
	// 创建文字


	// 图片居中
	Image->setPosX(Window::getWidth() / 2  );


	// 将精灵添加到 panel 节点
	g_Panel->addChild(Image);


	//获取排行榜数据
	
	vector<node> list = db.getRank(1);

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

	auto textTopic = gcnew Text(L"第一关");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275, 300);
	g_Panel->addChild(textTopic);
	for (int i = 0; i < list.size(); i++) {

		string s0 = list[i].name;
		auto text = gcnew Text(RankScene::String2WString(s0));
		text->setPos(445 , 110 + 42 * i);
		text->setStyle(style);
		g_Panel->addChild(text);

		int i1 = list[i].score;
		string s1 = to_string(i1);
		auto text1 = gcnew Text(RankScene::String2WString(s1));
		text1->setPos(595 , 110 + 42 * i);
		g_Panel->addChild(text1);
	}

}

void InitRound2()
{
	// 创建图片
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	// 图片居中
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() *1);

	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(Image);

	//获取排行榜数据
	
	vector<node> list = db.getRank(2);

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

	auto textTopic = gcnew Text(L"第二关");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275 + Window::getWidth() * 1, 300);
	g_Panel->addChild(textTopic);
	for (int i = 0; i < list.size(); i++) {

		string s0 = list[i].name;
		auto text = gcnew Text(RankScene::String2WString(s0));
		text->setPos(445 + Window::getWidth() * 1, 110 + 42 * i);
		text->setStyle(style);
		g_Panel->addChild(text);

		int i1 = list[i].score;
		string s1 = to_string(i1);
		auto text1 = gcnew Text(RankScene::String2WString(s1));
		text1->setPos(595 + Window::getWidth() * 1, 110 + 42 * i);
		g_Panel->addChild(text1);
	}


}

void InitRound3()
{
	// 创建图片
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	// 图片居中
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() *2);


	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(Image);


	//获取排行榜数据


	vector<node> list = db.getRank(3);

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

	auto textTopic = gcnew Text(L"第三关");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275 + Window::getWidth() * 2, 300);
	g_Panel->addChild(textTopic);
	for (int i = 0; i < list.size(); i++) {

		string s0 = list[i].name;
		auto text = gcnew Text(RankScene::String2WString(s0));
		text->setPos(445 + Window::getWidth() * 2, 110 + 42 * i);
		text->setStyle(style);
		g_Panel->addChild(text);

		int i1 = list[i].score;
		string s1 = to_string(i1);
		auto text1 = gcnew Text(RankScene::String2WString(s1));
		text1->setPos(595 + Window::getWidth() * 2, 110 + 42 * i);
		g_Panel->addChild(text1);
	}

}

void InitRound4()
{
	// 创建图片
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	
	// 图片居中
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() * 3);
	

	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(Image);


	//获取排行榜数据

	vector<node> list = db.getRank(4);

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

	auto textTopic = gcnew Text(L"第四关");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275 + Window::getWidth() * 3, 300);
	g_Panel->addChild(textTopic);

	for (int i = 0; i < list.size(); i++) {

		string s0 = list[i].name;
		auto text = gcnew Text(RankScene::String2WString(s0));
		text->setPos(445 + Window::getWidth() * 3, 110 + 42 * i);
		text->setStyle(style);
		g_Panel->addChild(text);

		int i1 = list[i].score;
		string s1 = to_string(i1);
		auto text1 = gcnew Text(RankScene::String2WString(s1));
		text1->setPos(595 + Window::getWidth() * 3, 110 + 42 * i);
		g_Panel->addChild(text1);
	}

}

void InitRound5()
{
	// 创建图片
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	// 图片居中
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() * 4);


	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(Image);


	//获取排行榜数据

	vector<node> list = db.getRank(5);

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

	auto textTopic = gcnew Text(L"第五关");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275 + Window::getWidth() * 4, 300);
	g_Panel->addChild(textTopic);

	for (int i = 0; i < list.size(); i++) {

		string s0 = list[i].name;
		auto text = gcnew Text(RankScene::String2WString(s0));
		text->setPos(445 + Window::getWidth() * 4, 110 + 42 * i);
		text->setStyle(style);
		g_Panel->addChild(text);

		int i1 = list[i].score;
		string s1 = to_string(i1);
		auto text1 = gcnew Text(RankScene::String2WString(s1));
		text1->setPos(595 + Window::getWidth() * 4, 110 + 42 * i);
		g_Panel->addChild(text1);
	}


}

void InitRound6()
{
	// 创建图片
	auto EgyptImage4 = gcnew Sprite(L"res/ranklist.png");
	EgyptImage4->setPosY(Window::getHeight() / 2 );

	// 图片居中
	EgyptImage4->setPosX(Window::getWidth() / 2 + Window::getWidth() * 5);


	// 将精灵添加到 panel 节点
	g_Panel->addChild(EgyptImage4);


	//获取排行榜数据

	vector<node> list = db.getRank(6);

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

	auto textTopic = gcnew Text(L"第六关");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275 + Window::getWidth() * 5, 300);
	g_Panel->addChild(textTopic);

	for (int i = 0; i < list.size(); i++) {

		string s0 = list[i].name;
		auto text = gcnew Text(RankScene::String2WString(s0));
		text->setPos(445 + Window::getWidth() * 5, 110 + 42 * i);
		text->setStyle(style);
		g_Panel->addChild(text);

		int i1 = list[i].score;
		string s1 = to_string(i1);
		auto text1 = gcnew Text(RankScene::String2WString(s1));
		text1->setPos(595 + Window::getWidth() * 5, 110 + 42 * i);
		g_Panel->addChild(text1);
	}

}

void InitButton()
{
	//// 创建开始按钮
	//auto startBtn = gcnew Button;
	//// 设置按钮图片
	//startBtn->setNormal(gcnew Sprite(L"res/LS07.png"));
	//// 设置按钮被选中时的图片
	//startBtn->setSelected(gcnew Sprite(L"res/LS08.png"));
	//// 设置按钮禁用时的图片
	//startBtn->setDisabled(gcnew Sprite(L"res/LS09.png"));
	//// 设置按钮位置
	//startBtn->setPos(Window::getWidth() / 2, Window::getHeight() - 80);
	//// 添加开始按钮
	//g_Scene->addChild(startBtn);

	// 创建左选按钮
	g_LeftButton = gcnew Button;
	g_LeftButton->setNormal(gcnew Sprite(L"res/LS01.png"));
	g_LeftButton->setSelected(gcnew Sprite(L"res/LS02.png"));
	g_LeftButton->setDisabled(gcnew Sprite(L"res/LS03.png"));
	g_LeftButton->setPosX(g_LeftButton->getWidth() / 2);
	g_LeftButton->setPosY((Window::getHeight() - g_LeftButton->getHeight()) / 2);
	g_LeftButton->setEnable(false);
	g_Scene->addChild(g_LeftButton);

	// 点击左按钮执行 ClickLeft 函数
	g_LeftButton->setClickFunc(ClickLeft);

	// 创建右选按钮
	g_RightButton = gcnew Button();
	g_RightButton->setNormal(gcnew Sprite(L"res/LS04.png"));
	g_RightButton->setSelected(gcnew Sprite(L"res/LS05.png"));
	g_RightButton->setDisabled(gcnew Sprite(L"res/LS06.png"));
	g_RightButton->setPosX(Window::getWidth() - g_RightButton->getWidth() / 2);
	g_RightButton->setPosY((Window::getHeight() - g_RightButton->getHeight()) / 2);
	g_Scene->addChild(g_RightButton);

	// 点击右按钮执行 ClickRight 函数
	g_RightButton->setClickFunc(ClickRight);
}

void ClickLeft()
{

	// 按下左选按钮后，把右选按钮启动
	g_RightButton->setEnable(true);
	// level 减一
	g_Level--;
	// 移动 panel
	MovePanel();

	// level 为 0 时，禁用左选按钮
	if (g_Level == 0)
	{
		g_LeftButton->setEnable(false);
	}
}

void ClickRight()
{
	// 按下右选按钮后，把左选按钮启动
	g_LeftButton->setEnable(true);
	// level 加一
	g_Level++;
	// 移动 panel
	MovePanel();

	// level 为 1 时，禁用右选按钮
	if (g_Level == 5)
	{
		g_RightButton->setEnable(false);
	}
}
void MovePanel()
{
	// 创建目标点
	auto point = Point(-Window::getWidth() * g_Level, 0);
	// 创建移动动画
	auto action = gcnew MoveTo(0.5f, point);
	// 停止 panel 的所有动画
	g_Panel->stopAllActions();
	// 执行新动画
	g_Panel->runAction(action);
}
