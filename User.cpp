#include "User.h"


//构造函数，默认游客 
User::User()
{
	this->name = "游客";
	this->taskGrade = new int[6];
	//初始化步数和分数为0，表示暂未挑战
	for (int i = 0; i < 6; i++)
	{
		taskGrade[i] = 0;
	}
	this->limTimeGrade = 0;
	this->isTraveler = true; //默认是游客
}

//设置用户名
void User::setName(std::string name)
{
	this->name = name;
}


//获取用户名
std::string User::getName()
{
	return this->name;
}


////返回是否是游客，是为true
//bool User::ifIsTraveler()
//{
//	return this->isTraveler;
//}
//
// //设置为非游客注册玩家
//void User::setLogined()
//{
//	this->isTraveler = false;
//}