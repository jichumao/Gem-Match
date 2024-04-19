#pragma once

#include <QWidget>
#include "ui_Register.h"
#include <string>
#include <QMessageBox>
#include "DataBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QWidget
{
	Q_OBJECT

public:
	Register(QWidget *parent = Q_NULLPTR);
	~Register();

private:
	Ui::Register *ui;

private slots:
	void reg(); //×¢²á°´Å¥µÄ²Ûº¯Êý
};
