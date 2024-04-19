#include "Smtp.h"
#include<QDebug>

Smtp::Smtp()
{
    this->username = "2539496792@qq.com";
    this->password = "kbzuuegahcundjhj";
}

void Smtp::send(std::string recvaddr, std::string subject, std::string content)
{
    this->recvaddr = QString::fromStdString(recvaddr).toUtf8();
    this->subject = QString::fromStdString(subject);
    this->content = QString::fromStdString(content);
    QByteArray usernametmp = this->username;
    QByteArray recvaddrtmp = this->recvaddr;

    clientsocket = new QTcpSocket();
    this->clientsocket->connectToHost("smtp.qq.com", 25, QTcpSocket::ReadWrite);
    this->clientsocket->waitForConnected(1000);
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;


    this->clientsocket->write("HELO smtp.163.com\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write("AUTH LOGIN\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write(username.toBase64().append("\r\n"));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write(password.toBase64().append("\r\n"));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write(mailfrom.append(usernametmp.append(">\r\n")));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write("data\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;


    usernametmp = this->username;
    recvaddrtmp = this->recvaddr;

    this->clientsocket->write(prefrom.append(usernametmp.append("\r\n")));
    this->clientsocket->write(preto.append(recvaddrtmp.append("\r\n")));
    this->clientsocket->write(presubject.append(this->subject.toLocal8Bit().append("\r\n")));
    this->clientsocket->write("\r\n");
    this->clientsocket->write(this->content.toLocal8Bit().append("\r\n"));
    this->clientsocket->write(".\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;

    this->clientsocket->write("quit\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    qDebug() << recvdata;
}

Smtp::~Smtp()
{
    delete this->clientsocket;
}