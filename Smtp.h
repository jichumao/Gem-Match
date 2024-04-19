#ifndef SMTP_H
#define SMTP_H
#include<QByteArray>
#include<QString>
#include <string>
#include<QtNetwork/qtcpsocket>
//#include <stdafx.h>
//#include<QTcpSocket>

class Smtp
{
public:
    Smtp();
    ~Smtp();
    void send(std::string recvaddr, std::string subject, std::string content);
private:
    QTcpSocket* clientsocket;
    QByteArray username;
    QByteArray password;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject = "subject:";
    QString subject;                //����
    QString content;                //��������
    QByteArray recvdata;            //���յ�������
};

#endif // SMTP_H