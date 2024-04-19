#pragma execution_character_set("utf-8")
#include "forgetPassword.h"

forgetPassword::forgetPassword(QWidget *parent)
	: QWidget(parent),ui(new Ui::forgetPassword)
{
	
	ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(send())); //发送验证码
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(confirm())); //确定修改密码
}

forgetPassword::~forgetPassword()
{
	delete ui;
}

//提交忘记密码，点确认
void forgetPassword::confirm()
{
	QString name = this->ui->lineEdit_4->text();
	QString passCode = this->ui->lineEdit_2->text();
	QString pass1 = this->ui->lineEdit_3->text();
	QString pass2 = this->ui->lineEdit->text();

	if (name == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入用户名!");
		return;
	}

	if (passCode == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入验证码!");
		return;
	}

	if (pass1 == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入新密码!");
		return;
	}
	if (pass2 == "")
	{
		QMessageBox::about(nullptr, "提示", "请确认新密码!");
		return;
	}



	//如果密码位数不和要求
	if (pass1.length() > 16 || pass1.length() < 6)
	{
		QMessageBox::about(nullptr, "提示", "密码长度应为6-16位!");
		this->ui->lineEdit_3->setText(nullptr);
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

	//检查验证码
	if (passCode != QString::number(this->code))
	{
		QMessageBox::about(nullptr, "提示", "验证码输入错误!");
		this->ui->lineEdit_2->setText(nullptr);
		return;
	}
	else
	{
		//连接数据库，修改密码
		
		bool back;
		back = db2.changePass(name.toStdString(), pass1.toStdString());
		if (back)
		{
			QMessageBox::about(nullptr, "消息", "密码修改成功!");
			this->close();
		}
		else
			QMessageBox::about(nullptr, "提示", "密码修改失败!");
	}
}

//发送验证码
void forgetPassword::send()
{
	if (ui->lineEdit_4->text() == "")
	{
		QMessageBox::about(nullptr, "提示", "请输入昵称!");
		return;
	}
	//生成随机四位验证码
	srand((int)time(0));
	code = rand() % 8999 + 1000;
//	DataBase db;
	string name = ui->lineEdit_4->text().toStdString();
	string mail = db2.getMail(name); //查询用户邮箱
	//如果输入用户不存在，报错
	if (mail == "")
	{
		QMessageBox::about(nullptr, "提示", "您输入的用户不存在!");
		return;
	}
	else
	{
		//发送邮件
		Smtp sender;
		string content = "亲爱的玩家"+name+":  您好，您的开心消消乐重置密码验证码为:"+std::to_string(code);
		sender.send(mail, "开心消消乐重置密码", content);
		string ss = "已发送验证码到您的邮箱" + mail + "中!";
		QMessageBox::about(nullptr, "提示", QString::fromStdString(ss));
	}
}