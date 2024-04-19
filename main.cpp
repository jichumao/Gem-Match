#include "login.h"
#include <QtWidgets/QApplication>

//#include "stdafx.h"
#include<windows.h>
#include"DataBase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;

    w.show();
    return a.exec();
}
