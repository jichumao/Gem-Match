#pragma execution_character_set("utf-8")

#include "Register.h"


Register::Register(QWidget *parent)
	: QWidget(parent), ui(new Ui::Register)
{
	ui->setupUi(this);
	//�����źźͲ�
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(reg()));
}

Register::~Register()
{
	delete ui;
}

//�ۺ���
void Register::reg()
{
	string name = this->ui->lineEdit_2->text().toUtf8();
	string email = this->ui->lineEdit_3->text().toUtf8();
	string pass1 = this->ui->lineEdit_4->text().toUtf8();
	string pass2 = this->ui->lineEdit->text().toUtf8();

	if (name == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "�������û���!");
		return;
	}

	if (email == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "����������!");
		return;
	}

	if (pass1 == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "����������!");
		return;
	}
	if (pass2 == "")
	{
		QMessageBox::about(nullptr, "��ʾ", "��ȷ������!");
		return;
	}

	

	//�������λ������Ҫ��
	if (pass1.length() > 16 || pass1.length()<6)
	{
		QMessageBox::about(nullptr, "��ʾ", "���볤��ӦΪ6-16λ!");
		this->ui->lineEdit_4->setText(nullptr);
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

	//������Ϲ淶�����ú���ע��
	DataBase db;
	//����Ѿ���ע��
	if (!db.reg(name, pass1))
	{
		QMessageBox::about(nullptr, "��ʾ", "���û����Ѵ���!");
		this->ui->lineEdit_2->setText(nullptr);
		return;
	}
	else
	{
		//��¼����
		db.mail(name, email);
		QMessageBox::about(nullptr, "��Ϣ", "ע��ɹ�!");
	}

	this->close();

}