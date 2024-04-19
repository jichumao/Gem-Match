#pragma execution_character_set("utf-8")

#include "Register.h"


Register::Register(QWidget *parent)
	: QWidget(parent), ui(new Ui::Register)
{
	ui->setupUi(this);
	//关联信号和槽
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(reg()));
}

Register::~Register()
{
	delete ui;
}

//槽函数
void Register::reg()
{
	string name = this->ui->lineEdit_2->text().toUtf8();
	string email = this->ui->lineEdit_3->text().toUtf8();
	string pass1 = this->ui->lineEdit_4->text().toUtf8();
	string pass2 = this->ui->lineEdit->text().toUtf8();

	if (name == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入用户名!");
		return;
	}

	if (email == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入邮箱!");
		return;
	}

	if (pass1 == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入密码!");
		return;
	}
	if (pass2 == "")
	{
		QMessageBox::about(nullptr, "提示", "请确认密码!");
		return;
	}

	

	//如果密码位数不和要求
	if (pass1.length() > 16 || pass1.length()<6)
	{
		QMessageBox::about(nullptr, "提示", "密码长度应为6-16位!");
		this->ui->lineEdit_4->setText(nullptr);
		this->ui->lineEdit->setText(nullptr);
		return;
	}

	//两次输入不一致
	if (pass1 != pass2)
	{
		QMessageBox::about(nullptr, "提示", "两次密码输入不一致!");
		this->ui->lineEdit->setText(nullptr);
		return;
	}

	//输入符合规范，调用函数注册
	DataBase db;
	//如果已经被注册
	if (!db.reg(name, pass1))
	{
		QMessageBox::about(nullptr, "提示", "该用户名已存在!");
		this->ui->lineEdit_2->setText(nullptr);
		return;
	}
	else
	{
		//记录邮箱
		db.mail(name, email);
		QMessageBox::about(nullptr, "消息", "注册成功!");
	}

	this->close();

}