#pragma once
#include "ui_forgetPassword.h"
#include <QWidget>
#include<QMessageBox>
#include<string>
#include<ctime>
#include "DataBase.h"
#include "Smtp.h"
QT_BEGIN_NAMESPACE
namespace Ui { class forgetPassword; }
QT_END_NAMESPACE

class forgetPassword : public QWidget
{
	Q_OBJECT

public:
	forgetPassword(QWidget *parent = Q_NULLPTR);
	~forgetPassword();

private:
	Ui::forgetPassword *ui;
	int code;
	DataBase db2;

private slots:
	void send();
	void confirm();
};
