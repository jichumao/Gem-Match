#include "User.h"


//���캯����Ĭ���ο� 
User::User()
{
	this->name = "�ο�";
	this->taskGrade = new int[6];
	//��ʼ�������ͷ���Ϊ0����ʾ��δ��ս
	for (int i = 0; i < 6; i++)
	{
		taskGrade[i] = 0;
	}
	this->limTimeGrade = 0;
	this->isTraveler = true; //Ĭ�����ο�
}

//�����û���
void User::setName(std::string name)
{
	this->name = name;
}


//��ȡ�û���
std::string User::getName()
{
	return this->name;
}


////�����Ƿ����οͣ���Ϊtrue
//bool User::ifIsTraveler()
//{
//	return this->isTraveler;
//}
//
// //����Ϊ���ο�ע�����
//void User::setLogined()
//{
//	this->isTraveler = false;
//}