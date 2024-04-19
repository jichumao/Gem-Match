#pragma execution_character_set("utf-8")
#include "forgetPassword.h"

forgetPassword::forgetPassword(QWidget *parent)
	: QWidget(parent),ui(new Ui::forgetPassword)
{
	
	ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(send())); //������֤��
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(confirm())); //ȷ���޸�����
}

forgetPassword::~forgetPassword()
{
	delete ui;
}

//�ύ�������룬��ȷ��
void forgetPassword::confirm()
{
	QString name = this->ui->lineEdit_4->text();
	QString passCode = this->ui->lineEdit_2->text();
	QString pass1 = this->ui->lineEdit_3->text();
	QString pass2 = this->ui->lineEdit->text();

	if (name == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "�������û���!");
		return;
	}

	if (passCode == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "��������֤��!");
		return;
	}

	if (pass1 == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "������������!");
		return;
	}
	if (pass2 == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "��ȷ��������!");
		return;
	}



	//�������λ������Ҫ��
	if (pass1.length() > 16 || pass1.length() < 6)
	{
		QMessageBox::about(nullptr, "��ʾ", "���볤��ӦΪ6-16λ!");
		this->ui->lineEdit_3->setText(nullptr);
		this->ui->lineEdit->setText(nullptr);
		return;
	}

	//�������벻һ��
	if (pass1 != pass2)
	{
		QMessageBox::about(nullptr, "��ʾ", "�����������벻һ��!");
		this->ui->lineEdit->setText(nullptr);
		return;
	}

	//�����֤��
	if (passCode != QString::number(this->code))
	{
		QMessageBox::about(nullptr, "��ʾ", "��֤���������!");
		this->ui->lineEdit_2->setText(nullptr);
		return;
	}
	else
	{
		//�������ݿ⣬�޸�����
		
		bool back;
		back = db2.changePass(name.toStdString(), pass1.toStdString());
		if (back)
		{
			QMessageBox::about(nullptr, "��Ϣ", "�����޸ĳɹ�!");
			this->close();
		}
		else
			QMessageBox::about(nullptr, "��ʾ", "�����޸�ʧ��!");
	}
}

//������֤��
void forgetPassword::send()
{
	if (ui->lineEdit_4->text() == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "�������ǳ�!");
		return;
	}
	//���������λ��֤��
	srand((int)time(0));
	code = rand() % 8999 + 1000;
//	DataBase db;
	string name = ui->lineEdit_4->text().toStdString();
	string mail = db2.getMail(name); //��ѯ�û�����
	//��������û������ڣ�����
	if (mail == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "��������û�������!");
		return;
	}
	else
	{
		//�����ʼ�
		Smtp sender;
		string content = "�װ������"+name+":  ���ã����Ŀ�������������������֤��Ϊ:"+std::to_string(code);
		sender.send(mail, "������������������", content);
		string ss = "�ѷ�����֤�뵽��������" + mail + "��!";
		QMessageBox::about(nullptr, "��ʾ", QString::fromStdString(ss));
	}
}