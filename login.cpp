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

	//关闭登陆窗口
	this->close();

	//初始化easy2d窗口
	if (Game::init(L"HappyPop", 1024, 640))
	{
		//设置窗口图标
		Window::setIcon(IDI_ICON1);
		//加载图片和音乐资源
		ResLoader::init();
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);
		//创建 StartScene
		auto scene = gcnew StartScene();
		// 创建淡入淡出式切换动画
		auto transition = gcnew FadeTransition(1);
		// 进入 StartScene，最后的参数 false 表示不再返回当前场景
		SceneManager::enter(scene, transition, false);
		Game::start();
	}
};

void login::loginNow() {

	string name = this->ui->log_act->text().toUtf8(); //获取用户名
	string pass = this->ui->log_psd->text().toUtf8(); //密码

	if (name == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入用户名!");
		return;
	}
	if (pass == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入密码!");
		return;
	}
	DataBase db;

	//返回0未找到用户名，返回1密码错误，返回2成功
	int back = db.login(name, pass);
	//如果未找到用户名，报错
	if (back == 0)
	{
		QMessageBox::about(nullptr, "提示", "该用户名不存在!");
		this->ui->log_act->setText(nullptr);
		this->ui->log_psd->setText(nullptr);

		return;
	}
	//密码错误
	if (back == 1)
	{
		QMessageBox::about(nullptr, "提示", "密码错误!");
		this->ui->log_psd->setText(nullptr);

		return;
	}
	//用户名密码正确
	DataBase::player.setName(name);
	DataBase::player.isTraveler=false;
    //关闭登陆窗口
	this->close();
	//初始化easy2d窗口
	if (Game::init(L"HappyPop", 1024,640))
	{
		//设置窗口图标
		Window::setIcon(IDI_ICON1);
		//加载图片和音乐资源
		ResLoader::init();
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);
		//创建 StartScene

		auto scene = gcnew StartScene();
		// 创建淡入淡出式切换动画
		auto transition = gcnew FadeTransition(1);
		// 进入 StartScene，最后的参数 false 表示不再返回当前场景
		SceneManager::enter(scene, transition, false);
		Game::start();
	}

	//下面那句话 不删的话 关了游戏有异常
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



