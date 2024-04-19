#pragma execution_character_set("utf-8")

#include "login.h"
#include <iostream>
#include <QMessageBox>
#include "resource.h"
#include "ResLoader.h"
#include "StartScene.h"
#include "Register.h"
#include "mysetting.h"
#include "forgetPassword.h"
login::login(QWidget *parent)
    : QWidget(parent)
{
    ui->setupUi(this);
	

}

login::~login() {

};


void login::tour() {

	//�رյ�½����
	this->close();

	//��ʼ��easy2d����
	if (Game::init(L"HappyPop", 1024, 640))
	{
		//���ô���ͼ��
		Window::setIcon(IDI_ICON1);
		//����ͼƬ��������Դ
		ResLoader::init();
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		Node::setDefaultAnchor(0.5f, 0.5f);
		//���� StartScene
		auto scene = gcnew StartScene();
		// �������뵭��ʽ�л�����
		auto transition = gcnew FadeTransition(1);
		// ���� StartScene�����Ĳ��� false ��ʾ���ٷ��ص�ǰ����
		SceneManager::enter(scene, transition, false);
		Game::start();
	}
};

void login::loginNow() {

	string name = this->ui->log_act->text().toUtf8(); //��ȡ�û���
	string pass = this->ui->log_psd->text().toUtf8(); //����

	if (name == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "�������û���!");
		return;
	}
	if (pass == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "����������!");
		return;
	}
	DataBase db;

	//����0δ�ҵ��û���������1������󣬷���2�ɹ�
	int back = db.login(name, pass);
	//���δ�ҵ��û���������
	if (back == 0)
	{
		QMessageBox::about(nullptr, "��ʾ", "���û���������!");
		this->ui->log_act->setText(nullptr);
		this->ui->log_psd->setText(nullptr);

		return;
	}
	//�������
	if (back == 1)
	{
		QMessageBox::about(nullptr, "��ʾ", "�������!");
		this->ui->log_psd->setText(nullptr);

		return;
	}
	//�û���������ȷ
	DataBase::player.setName(name);
	DataBase::player.isTraveler=false;
    //�رյ�½����
	this->close();
	//��ʼ��easy2d����
	if (Game::init(L"HappyPop", 1024,640))
	{
		//���ô���ͼ��
		Window::setIcon(IDI_ICON1);
		//����ͼƬ��������Դ
		ResLoader::init();
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		Node::setDefaultAnchor(0.5f, 0.5f);
		//���� StartScene

		auto scene = gcnew StartScene();
		// �������뵭��ʽ�л�����
		auto transition = gcnew FadeTransition(1);
		// ���� StartScene�����Ĳ��� false ��ʾ���ٷ��ص�ǰ����
		SceneManager::enter(scene, transition, false);
		Game::start();
	}

	//�����Ǿ仰 ��ɾ�Ļ� ������Ϸ���쳣
	   Game::destroy();
}

void login::registerNow() {
	Register* r =new Register();
	r->show();
	
}

void login::forgetPsd() {
	forgetPassword*f =new forgetPassword();
	f->show();
	
}



