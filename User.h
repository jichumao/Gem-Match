#pragma once
#ifndef USER_H_
#define USER_H_

#include<string>

class User {
private:
	std::string name = "�ο�";//�û�����
	std::string password;//�û�����
	int number;//�û���ţ�����ע��˳�����������������а����Ϣ
	//��ע��ʱ�����û������ʼ�� taskGrade = new int[6]��ÿ��Ԫ��Ϊ0
	//���¼ʱ�����ݿ�/�ļ��ж�ȡ�����Ϣ����ȡÿ��Ԫ��ֵ

public:
	bool isTraveler; //�Ƿ����οͣ����ο�Ϊtrue
	int* taskGrade;//�ֱ��Ŵ���ģʽ6�صķ�����ÿ�ؽ���ʱ���£��������ݿ�/�ļ�
	//��ע��ʱ�����û������ʼ�� taskGrade = new int[6]��ÿ��Ԫ��Ϊ0
	//���¼ʱ�����ݿ��ж�ȡ�����Ϣ����ȡÿ��Ԫ��ֵ
	int limTimeGrade;//����ģʽ����ҷ���
	User(); //Ĭ�Ϲ��캯����Ĭ���ο�
//	User(std::string name, bool isTraveler); //���캯��������Ϊ�û������Ƿ�Ϊ�ο� 
	void setName(std::string name); //�����û���
	std::string getName(); //��ȡ�û���
	//bool ifIsTraveler(); //�����Ƿ����οͣ���Ϊtrue
	//void setLogined(); //����Ϊ���ο�ע�����
	int getNumber() { return number; }//�����û����



};

#endif // !USER_H_

