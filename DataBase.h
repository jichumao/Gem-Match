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
	string name; //玩家昵称
	int score; //步数或得分
}node;

class DataBase
{
public:
	static User player;
	DataBase(); //构造器
	~DataBase(); //析构函数，释放资源
	void connect();
	int login(string name, string pass); //登录，比对用户名密码;返回0未找到用户名，返回1密码错误，返回2成功
	bool reg(string name, string pass); //注册，返回是否注册成功，不成功则是用户已存在
	int getScore(int, std::string); //获取用户关卡数的分数，1-6为闯关模式步数，7为竞速模式分数;返回0则是暂无记录
	bool setScore(int num, int score, string name); //设置用户关卡分数或步数
	vector<node> getRank(int num); //获得指定关卡的排行，返回排行榜向量（有序）
	void sort(vector<node>* rank, int num); //给结构体数组排序，1-6关升序排，第七关降序
	bool judgeRank(int num, int score, string name); //判断能否进排行榜，如果能，要更新数据库排行榜内容
	void mail(string name, string mail); //记录用户邮箱
	string getMail(string name); //获取指定用户邮箱
	bool changePass(string name, string newPass); //修改用户密码

private:
	MYSQL mysql; //一个数据库结构体
	MYSQL_RES* res; //一个结果集结构体
	MYSQL* sock; //连接句柄

};
#pragma once
