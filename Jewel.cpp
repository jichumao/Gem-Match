#include "Jewel.h"
#include "GameScene.h"
#include <string>
#include <windows.h>
#include <ctime>

#define GRID_LENGTH 72.5
#define INTERTIME 0.2f
#define WAITTIME 0.8f


//void Jewel::wait_for_a_while()
//{
//	float secs = WAITTIME;
//	clock_t delay = secs * CLOCKS_PER_SEC;
//	clock_t start = clock();
//	//printf("Waiting...\n");
//	while (clock() - start < delay);
//	//printf("OK\n");
//	return;
//}


Jewel::Jewel()
{
	this->pic_num = 0;
	this->pos_col = 0;
	this->pos_row = 0;
	isSelected = false;
	jewel_btn = gcnew Button(gcnew Sprite(L"res\\1_01.png"));
	jewel_btn->setClickFunc(std::bind(&Jewel::Select, this));
	this->addChild(jewel_btn);
	border = gcnew Sprite(L"res\\onChoosing.png");
	border->setScale(0.5f);
	border->setPosX(jewel_btn->getWidth() / 2);
	border->setPosY(jewel_btn->getHeight() / 2);
	jewel_btn->addChild(border);
	border->setVisible(isSelected);
}

Jewel::Jewel(int pic_num)
{
	this->pic_num = pic_num;
	this->pos_col = 0;
	this->pos_row = 0;
	isSelected = false;
	std::string path = "res\\1_0" + std::to_string(this->pic_num) + ".png";
	String widename = NarrowToWide(path);
	jewel_btn = gcnew Button(gcnew Sprite(widename));
	jewel_btn->setClickFunc(std::bind(&Jewel::Select, this));
	this->addChild(jewel_btn);
	border = gcnew Sprite(L"res\\onChoosing.png");
	border->setScale(0.5f);
	border->setPosX(jewel_btn->getWidth() / 2);
	border->setPosY(jewel_btn->getHeight() / 2);
	jewel_btn->addChild(border);
	border->setVisible(isSelected);
}

Jewel::Jewel(const Jewel& obj)
{
	this->pic_num = obj.pic_num;
	this->pos_col = obj.pos_col;
	this->pos_row = obj.pos_row;
	isSelected = false;
	std::string path = "res\\1_0" + std::to_string(this->pic_num) + ".png";
	String widename = NarrowToWide(path);
	jewel_btn = gcnew Button(gcnew Sprite(widename));
	jewel_btn->setClickFunc(std::bind(&Jewel::Select, this));
	this->addChild(jewel_btn);
	border = gcnew Sprite(L"res\\onChoosing.png");
	border->setScale(0.5f);
	border->setPosX(jewel_btn->getWidth() / 2);
	border->setPosY(jewel_btn->getHeight() / 2);
	jewel_btn->addChild(border);
	border->setVisible(isSelected);
}

void Jewel::Select()
{
	if (!this)
	{
		return;
	}
	// ��ȡ��ť״̬
	if (!isSelected)
	{
		isSelected = true;
		border->setVisible(isSelected);
		GameScene::add_selected_jewels_numbers();
	}
	else
	{
		isSelected = false;
		border->setVisible(isSelected);
		GameScene::minu_selected_jewels_numbers();
	}
	// ������Ϣ���ļ�
	Data::saveBool(L"isSelected", isSelected);
	
}


void Jewel::Exchange(Jewel* jewel1, Jewel* jewel2, float delay, bool ifReturn)
{
	//�������ƶ���
	auto moveRight = gcnew MoveBy(INTERTIME, Vector2(GRID_LENGTH, 0));

	//�������ƶ���
	auto moveLeft = gcnew MoveBy(INTERTIME, Vector2(-GRID_LENGTH, 0));

	//�������ƶ���
	auto moveup = gcnew MoveBy(INTERTIME, Vector2(0, GRID_LENGTH));

	//�������ƶ���
	auto movedown = gcnew MoveBy(INTERTIME, Vector2(0, -GRID_LENGTH));

	auto animation1 = gcnew MoveBy(0.0f, Vector2(0, 0));
	auto animation2 = gcnew MoveBy(0.0f, Vector2(0, 0));

	//ִ�ж���
	if (jewel1->getPosX() > jewel2->getPosX())
	{
		animation1 = moveLeft->clone();
		animation2 = moveRight->clone();
	}
	else if (jewel1->getPosX() < jewel2->getPosX())
	{
		animation1 = moveRight->clone();
		animation2 = moveLeft->clone();
	}
	else if (jewel1->getPosY() < jewel2->getPosY()) {

		animation1 = moveup->clone();
		animation2 = movedown->clone();
	}
	else {
		animation1 = movedown->clone();
		animation2 = moveup->clone();

	}

	auto delay1 = gcnew Delay(delay);
	auto sequence1 = gcnew Sequence({ delay1->clone(),animation1 });
	auto sequence2 = gcnew Sequence({ delay1->clone(),animation2 });


	if (!ifReturn)
	{
		jewel1->runAction(sequence1->clone());
		jewel2->runAction(sequence2->clone());
	}
	else
	{
		jewel1->runAction(gcnew Sequence({ sequence1->clone(), sequence2->clone() }));
		jewel2->runAction(gcnew Sequence({ sequence2->clone(), sequence1->clone() }));
		jewel1->isSelected = false;
		jewel2->isSelected = false;
	}

	jewel1->border->setVisible(false);
	jewel2->border->setVisible(false);
	//wait_for_a_while();
}																																																																																							



void Jewel::Fall(int fall_grids)
{
	//����һ�����䶯��
	auto fallTo = gcnew MoveBy(INTERTIME, Vector2(0.0f, (float)GRID_LENGTH * fall_grids));
	auto delay = gcnew Delay(0.3f);
	auto resume = gcnew CallFunc([]() {
		GameScene::canResume = true;
		GameScene::SetBtnEnabled(true);//�������Ž��������а�ť�ָ��ɵ��
		});
	this->runAction(gcnew Sequence({ delay, fallTo, delay, resume }));
	printf("%d falls\n", this->pic_num);
	//wait_for_a_while();
}
//
//void Jewel::Break(Jewel* jewel, double delay)
//{
//	// ����һ�����Ŷ�����1 �����ʧ
//	auto scaleTo = gcnew ScaleTo(0.3f, 0.0f);
//	auto delay1 = gcnew Delay(delay);
//	auto sequence1 = gcnew Sequence({ delay1->clone(),scaleTo });
//	jewel->runAction(sequence1);
//}

void Jewel::Break() {
	//��ֹ���亯������
	auto scaleTo = gcnew ScaleTo(INTERTIME, 0.0f);
	auto delay = gcnew Delay(INTERTIME);
	this->runAction(gcnew Sequence({ delay, scaleTo }));
	printf("%d breaks\n", this->pic_num);
	//Jewel::wait_for_a_while();//ͣ��һ��ʱ�����������亯������
}

Jewel::~Jewel()
{
}
