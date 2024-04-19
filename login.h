#pragma once

#include <QtWidgets/QWidget>
#include "ui_login.h"
#include <string>


class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = Q_NULLPTR);
    ~login();
    //std::string s;
  
private:
    Ui::loginClass* ui;
   

    private slots:
        void loginNow();
        void registerNow();
        void tour();
        void forgetPsd();
        //void sendCode(); //��������
        //void submit(); //ȷ��
};
