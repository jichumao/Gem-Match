#pragma once
#include "StartScene.h"
#include "ResLoader.h"
#include "PatternScene.h"
#include "RankScene.h"
#include <iostream>
#include "SpeedRankScene.h"
//---------------------------------------------------------
// ��������
//---------------------------------------------------------

void InitSpeed();
void InitRound1();
void InitRound2();
void InitRound3();
void InitRound4();
void InitRound5();
void InitRound6();
void InitButton();		// ���ذ�ť
void MovePanel();		// �ƶ��ؿ����
void ClickLeft();		// �����ť
void ClickRight();		// ����Ұ�ť

//---------------------------------------------------------
// ȫ�ֱ�������
//---------------------------------------------------------

Scene* g_Scene;		// ����
Node* g_Panel;		// �ؿ����
int		g_Level;		// ��ǰѡ�еĹؿ���
Button* g_LeftButton;	// ��ť
Button* g_RightButton;	// �Ұ�ť
DataBase db;
//---------------------------------------------------------
// ��������
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

	// ����һ���ճ���
	g_Scene = new Scene();
	// ���õ�ǰ�ؿ�Ϊ 0
	g_Level = 0;

	// ��������ͼ����
	auto background1 = gcnew Sprite(L"res/BG03.png");
	// ����ͼ������ʾ
	background1->setPos(Window::getSize() / 2);
	// ��ͼƬ��ӵ�������
	g_Scene->addChild(background1);

	//���÷��������澫��
	auto returnMain = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	auto returnMain_selected = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	returnMain->setScale(1.0f);
	returnMain_selected->setScale(0.8f);
	returnMain_selected->movePosY((returnMain->getHeight() - returnMain_selected->getHeight()) / 2);
	returnMain_selected->movePosX((returnMain_selected->getWidth() - returnMain_selected->getWidth()) / 2);
	//��ӷ������˵���ť
	auto returnMain_btn = gcnew Button(returnMain, returnMain_selected);
	// ���·��ذ�ť������ ���˵� ����
	returnMain_btn->setClickFunc([]
		{
			SceneManager::enter(gcnew StartScene());
		});
	returnMain_btn->setPos(Window::getWidth() - 50, Window::getHeight() - 50);
	this->addChild(returnMain_btn);

	//���÷��������澫��
	auto returnMain1 = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	auto returnMain_selected1 = gcnew Sprite(ResLoader::getImage(L"ReturnScene"));
	returnMain1->setScale(1.0f);
	returnMain_selected1->setScale(0.8f);
	returnMain_selected1->movePosY((returnMain1->getHeight() - returnMain_selected1->getHeight()) / 2);
	returnMain_selected1->movePosX((returnMain_selected1->getWidth() - returnMain_selected1->getWidth()) / 2);

	//��ӷ������˵���ť
	auto returnMain_btn1 = gcnew Button(returnMain1, returnMain_selected1);
	returnMain_btn1->setClickFunc([]
		{
			SceneManager::back();
		});

	returnMain_btn1->setPos(Window::getWidth() - 50, Window::getHeight() - 50);
	g_Scene->addChild(returnMain_btn1);


	// �����ؿ�ͼƬ�ϲ�Ϊ panel �ڵ�
	g_Panel = gcnew Node();
	g_Scene->addChild(g_Panel);

	// ���عؿ�ͼƬ
	
	InitRound1();
	InitRound2();
	InitRound3();
	InitRound4();
	InitRound5();
	InitRound6();

	// ��Ӱ�ť
	InitButton();

	//��ӽ��뾭��ģʽ��ť
	auto start = gcnew Sprite(ResLoader::getImage(L"StartGame"));
	auto start_btn = gcnew Button(start);

	start_btn->setClickFunc([]
		{
			SceneManager::enter(g_Scene, gcnew FadeTransition(0.6f));
		});

	start_btn->setPos(Window::getWidth() / 2 - 100, Window::getHeight() / 2 - 100);
	this->addChild(start_btn);
	
	//��ӽ��뾺��ģʽ��ť
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
	// ����ͼƬ
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );
	// ��������


	// ͼƬ����
	Image->setPosX(Window::getWidth() / 2  );


	// ��������ӵ� panel �ڵ�
	g_Panel->addChild(Image);


	//��ȡ���а�����
	
	vector<node> list = db.getRank(1);

	// ����������ʽ
	auto style = Text::Style();
	style.color = Color::White;          // ��ɫΪ��ɫ
	style.hasOutline = true;            // �����������
	style.outlineColor = Color::SkyBlue;    // ���������ɫ
	style.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style.wrapping = true;              // �����Զ�����
	style.wrappingWidth = 70;           // �����Զ����еĿ��Ϊ 70�����أ�

	// ����������ʽ2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // ��ɫΪ��ɫ
	style2.hasOutline = true;            // �����������
	style2.outlineColor = Color::Black;    // ���������ɫ
	style2.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style2.wrapping = true;              // �����Զ�����
	style2.wrappingWidth = 10;           // �����Զ����еĿ��Ϊ 70�����أ�

	auto textTopic = gcnew Text(L"��һ��");
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
	// ����ͼƬ
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	// ͼƬ����
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() *1);

	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(Image);

	//��ȡ���а�����
	
	vector<node> list = db.getRank(2);

	// ����������ʽ
	auto style = Text::Style();
	style.color = Color::White;          // ��ɫΪ��ɫ
	style.hasOutline = true;            // �����������
	style.outlineColor = Color::SkyBlue;    // ���������ɫ
	style.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style.wrapping = true;              // �����Զ�����
	style.wrappingWidth = 70;           // �����Զ����еĿ��Ϊ 70�����أ�

	// ����������ʽ2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // ��ɫΪ��ɫ
	style2.hasOutline = true;            // �����������
	style2.outlineColor = Color::Black;    // ���������ɫ
	style2.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style2.wrapping = true;              // �����Զ�����
	style2.wrappingWidth = 10;           // �����Զ����еĿ��Ϊ 70�����أ�

	auto textTopic = gcnew Text(L"�ڶ���");
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
	// ����ͼƬ
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	// ͼƬ����
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() *2);


	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(Image);


	//��ȡ���а�����


	vector<node> list = db.getRank(3);

	// ����������ʽ
	auto style = Text::Style();
	style.color = Color::White;          // ��ɫΪ��ɫ
	style.hasOutline = true;            // �����������
	style.outlineColor = Color::SkyBlue;    // ���������ɫ
	style.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style.wrapping = true;              // �����Զ�����
	style.wrappingWidth = 70;           // �����Զ����еĿ��Ϊ 70�����أ�

		// ����������ʽ2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // ��ɫΪ��ɫ
	style2.hasOutline = true;            // �����������
	style2.outlineColor = Color::Black;    // ���������ɫ
	style2.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style2.wrapping = true;              // �����Զ�����
	style2.wrappingWidth = 10;           // �����Զ����еĿ��Ϊ 70�����أ�

	auto textTopic = gcnew Text(L"������");
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
	// ����ͼƬ
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	
	// ͼƬ����
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() * 3);
	

	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(Image);


	//��ȡ���а�����

	vector<node> list = db.getRank(4);

	// ����������ʽ
	auto style = Text::Style();
	style.color = Color::White;          // ��ɫΪ��ɫ
	style.hasOutline = true;            // �����������
	style.outlineColor = Color::SkyBlue;    // ���������ɫ
	style.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style.wrapping = true;              // �����Զ�����
	style.wrappingWidth = 70;           // �����Զ����еĿ��Ϊ 70�����أ�

	// ����������ʽ2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // ��ɫΪ��ɫ
	style2.hasOutline = true;            // �����������
	style2.outlineColor = Color::Black;    // ���������ɫ
	style2.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style2.wrapping = true;              // �����Զ�����
	style2.wrappingWidth = 10;           // �����Զ����еĿ��Ϊ 70�����أ�

	auto textTopic = gcnew Text(L"���Ĺ�");
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
	// ����ͼƬ
	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2 );

	// ͼƬ����
	Image->setPosX(Window::getWidth() / 2 + Window::getWidth() * 4);


	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(Image);


	//��ȡ���а�����

	vector<node> list = db.getRank(5);

	// ����������ʽ
	auto style = Text::Style();
	style.color = Color::White;          // ��ɫΪ��ɫ
	style.hasOutline = true;            // �����������
	style.outlineColor = Color::SkyBlue;    // ���������ɫ
	style.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style.wrapping = true;              // �����Զ�����
	style.wrappingWidth = 70;           // �����Զ����еĿ��Ϊ 70�����أ�

		// ����������ʽ2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // ��ɫΪ��ɫ
	style2.hasOutline = true;            // �����������
	style2.outlineColor = Color::Black;    // ���������ɫ
	style2.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style2.wrapping = true;              // �����Զ�����
	style2.wrappingWidth = 10;           // �����Զ����еĿ��Ϊ 70�����أ�

	auto textTopic = gcnew Text(L"�����");
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
	// ����ͼƬ
	auto EgyptImage4 = gcnew Sprite(L"res/ranklist.png");
	EgyptImage4->setPosY(Window::getHeight() / 2 );

	// ͼƬ����
	EgyptImage4->setPosX(Window::getWidth() / 2 + Window::getWidth() * 5);


	// ��������ӵ� panel �ڵ�
	g_Panel->addChild(EgyptImage4);


	//��ȡ���а�����

	vector<node> list = db.getRank(6);

	// ����������ʽ
	auto style = Text::Style();
	style.color = Color::White;          // ��ɫΪ��ɫ
	style.hasOutline = true;            // �����������
	style.outlineColor = Color::SkyBlue;    // ���������ɫ
	style.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style.wrapping = true;              // �����Զ�����
	style.wrappingWidth = 70;           // �����Զ����еĿ��Ϊ 70�����أ�

		// ����������ʽ2
	auto style2 = Text::Style();
	style2.color = Color::LightSkyBlue;          // ��ɫΪ��ɫ
	style2.hasOutline = true;            // �����������
	style2.outlineColor = Color::Black;    // ���������ɫ
	style2.outlineWidth = 2.0;           // ������߿��Ϊ 2.0
	style2.wrapping = true;              // �����Զ�����
	style2.wrappingWidth = 10;           // �����Զ����еĿ��Ϊ 70�����أ�

	auto textTopic = gcnew Text(L"������");
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
	//// ������ʼ��ť
	//auto startBtn = gcnew Button;
	//// ���ð�ťͼƬ
	//startBtn->setNormal(gcnew Sprite(L"res/LS07.png"));
	//// ���ð�ť��ѡ��ʱ��ͼƬ
	//startBtn->setSelected(gcnew Sprite(L"res/LS08.png"));
	//// ���ð�ť����ʱ��ͼƬ
	//startBtn->setDisabled(gcnew Sprite(L"res/LS09.png"));
	//// ���ð�ťλ��
	//startBtn->setPos(Window::getWidth() / 2, Window::getHeight() - 80);
	//// ��ӿ�ʼ��ť
	//g_Scene->addChild(startBtn);

	// ������ѡ��ť
	g_LeftButton = gcnew Button;
	g_LeftButton->setNormal(gcnew Sprite(L"res/LS01.png"));
	g_LeftButton->setSelected(gcnew Sprite(L"res/LS02.png"));
	g_LeftButton->setDisabled(gcnew Sprite(L"res/LS03.png"));
	g_LeftButton->setPosX(g_LeftButton->getWidth() / 2);
	g_LeftButton->setPosY((Window::getHeight() - g_LeftButton->getHeight()) / 2);
	g_LeftButton->setEnable(false);
	g_Scene->addChild(g_LeftButton);

	// �����ťִ�� ClickLeft ����
	g_LeftButton->setClickFunc(ClickLeft);

	// ������ѡ��ť
	g_RightButton = gcnew Button();
	g_RightButton->setNormal(gcnew Sprite(L"res/LS04.png"));
	g_RightButton->setSelected(gcnew Sprite(L"res/LS05.png"));
	g_RightButton->setDisabled(gcnew Sprite(L"res/LS06.png"));
	g_RightButton->setPosX(Window::getWidth() - g_RightButton->getWidth() / 2);
	g_RightButton->setPosY((Window::getHeight() - g_RightButton->getHeight()) / 2);
	g_Scene->addChild(g_RightButton);

	// ����Ұ�ťִ�� ClickRight ����
	g_RightButton->setClickFunc(ClickRight);
}

void ClickLeft()
{

	// ������ѡ��ť�󣬰���ѡ��ť����
	g_RightButton->setEnable(true);
	// level ��һ
	g_Level--;
	// �ƶ� panel
	MovePanel();

	// level Ϊ 0 ʱ��������ѡ��ť
	if (g_Level == 0)
	{
		g_LeftButton->setEnable(false);
	}
}

void ClickRight()
{
	// ������ѡ��ť�󣬰���ѡ��ť����
	g_LeftButton->setEnable(true);
	// level ��һ
	g_Level++;
	// �ƶ� panel
	MovePanel();

	// level Ϊ 1 ʱ��������ѡ��ť
	if (g_Level == 5)
	{
		g_RightButton->setEnable(false);
	}
}
void MovePanel()
{
	// ����Ŀ���
	auto point = Point(-Window::getWidth() * g_Level, 0);
	// �����ƶ�����
	auto action = gcnew MoveTo(0.5f, point);
	// ֹͣ panel �����ж���
	g_Panel->stopAllActions();
	// ִ���¶���
	g_Panel->runAction(action);
}
