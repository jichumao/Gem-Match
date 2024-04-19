#pragma once
#include "SpeedRankScene.h"
#include "StartScene.h"
#include "ResLoader.h"
#include "PatternScene.h"
#include "RankScene.h"
#include <iostream>
#include <windows.h>
Scene* g_Scene_Speed;		// ����
Node* g_Panel_Speed;		// �ؿ����

using namespace std;

SpeedRankScene::SpeedRankScene()
{

	// ��������ͼ����
	auto background1 = gcnew Sprite(L"res/BG03.png");
	// ����ͼ������ʾ
	background1->setPos(Window::getSize() / 2);
	// ��ͼƬ��ӵ�������
	this->addChild(background1);


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
			SceneManager::back();
		});
	returnMain_btn->setPos(Window::getWidth() - 50, Window::getHeight() - 50);

	this->addChild(returnMain_btn);

	auto Image = gcnew Sprite(L"res/ranklist.png");
	Image->setPosY(Window::getHeight() / 2);
	//// ��������
	//auto Text = gcnew Sprite(L"res/LS10.png");
	//Text->setPosY(Window::getHeight() - 300);
	// ͼƬ����
	Image->setPosX(Window::getWidth() / 2);
	this->addChild(Image);

	//��ȡ���а�����
	DataBase db;
	vector<node> list = db.getRank(7);

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

	auto textTopic = gcnew Text(L"����ģʽ");
	textTopic->setScale(2.0f);
	textTopic->setStyle(style2);
	textTopic->setPos(275,300);
	this->addChild(textTopic);
	//��ӡ��Ϣ
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



