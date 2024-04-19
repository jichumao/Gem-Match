#include "WashButton.h"

WashButton::WashButton()
{
	auto btn_pic = gcnew RectShape(Size(100, 40));
	auto btn_pic_select = gcnew RectShape(Size(50, 10));
	// ���������ɫΪ��ɫ
	btn_pic->setFillColor(Color::Red);
	// ����������ɫΪ��ɫ
	btn_pic->setLineColor(Color::White);
	// ���������������Ϊ 2
	btn_pic->setStrokeWidth(2.0);
	auto btn_text = gcnew Text(L"Wash");
	btn_text->setPos(btn_pic->getWidth() / 2, btn_pic->getHeight() / 2);
	btn_pic->addChild(btn_text);
	this->setNormal(btn_pic);
	this->setSelected(btn_pic_select);
	btn_pic_select->setScale(0.7);
	btn_pic_select->movePosY((btn_pic->getHeight() - btn_pic_select->getHeight()) / 2);
	btn_pic_select->movePosX((btn_pic->getWidth() - btn_pic_select->getWidth()) / 2);
}

WashButton::~WashButton()
{

}
