#pragma once
#include <stdio.h>
#include <string>
#include "mysql.h"
#include <iostream>
#include <vector>
#include"user.h"

using namespace std;

typedef struct node
{
	string name; //����ǳ�
	int score; //������÷�
}node;

class DataBase
{
public:
	static User player;
	DataBase(); //������
	~DataBase(); //�����������ͷ���Դ
	void connect();
	int login(string name, string pass); //��¼���ȶ��û�������;����0δ�ҵ��û���������1������󣬷���2�ɹ�
	bool reg(string name, string pass); //ע�ᣬ�����Ƿ�ע��ɹ������ɹ������û��Ѵ���
	int getScore(int, std::string); //��ȡ�û��ؿ����ķ�����1-6Ϊ����ģʽ������7Ϊ����ģʽ����;����0�������޼�¼
	bool setScore(int num, int score, string name); //�����û��ؿ���������
	vector<node> getRank(int num); //���ָ���ؿ������У��������а�����������
	void sort(vector<node>* rank, int num); //���ṹ����������1-6�������ţ����߹ؽ���
	bool judgeRank(int num, int score, string name); //�ж��ܷ�����а�����ܣ�Ҫ�������ݿ����а�����
	void mail(string name, string mail); //��¼�û�����
	string getMail(string name); //��ȡָ���û�����
	bool changePass(string name, string newPass); //�޸��û�����

private:
	MYSQL mysql; //һ�����ݿ�ṹ��
	MYSQL_RES* res; //һ��������ṹ��
	MYSQL* sock; //���Ӿ��

};
#pragma once
