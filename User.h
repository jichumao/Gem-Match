#pragma once
#ifndef USER_H_
#define USER_H_

#include<string>

class User {
private:
	std::string name = "游客";//用户姓名
	std::string password;//用户密码
	int number;//用户编号，根据注册顺序决定，方便管理排行榜等信息
	//在注册时创建用户对象初始化 taskGrade = new int[6]，每个元素为0
	//或登录时从数据库/文件中读取玩家信息，读取每个元素值

public:
	bool isTraveler; //是否是游客：是游客为true
	int* taskGrade;//分别存放闯关模式6关的分数，每关结束时更新，存入数据库/文件
	//在注册时创建用户对象初始化 taskGrade = new int[6]，每个元素为0
	//或登录时从数据库中读取玩家信息，读取每个元素值
	int limTimeGrade;//竞速模式下玩家分数
	User(); //默认构造函数，默认游客
//	User(std::string name, bool isTraveler); //构造函数，参数为用户名和是否为游客 
	void setName(std::string name); //设置用户名
	std::string getName(); //获取用户名
	//bool ifIsTraveler(); //返回是否是游客，是为true
	//void setLogined(); //设置为非游客注册玩家
	int getNumber() { return number; }//返回用户编号



};

#endif // !USER_H_

