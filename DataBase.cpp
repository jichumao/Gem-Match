#pragma execution_character_set("utf-8")

#include "DataBase.h"
using namespace std;
User DataBase::player = User();
//构造器
DataBase::DataBase()
{
    cout << "gouzao" << endl;
    this->connect();
}

//连接数据库
void DataBase::connect()
{
    //初始化数据库
    mysql_init(&mysql);
    //设置编码方式
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    cout << "connect" << endl;
    //连接数据库
    //判断如果连接失败就把连接失败的信息显示出来，好进行对应修改。
    // mysql_real_connect参数：2.地址 3.mysql用户名 4.mysql密码 5.数据库名字 6.端口号
    if (mysql_real_connect(&mysql, "175.24.96.32", "commonuser", "commonuser", "common", 3306, NULL, 0) == NULL) {
        cout << (mysql_error(&mysql));
    }
    else cout << "successfully connected!" << endl;

}


//登录，比对用户名密码；返回0未找到用户名，返回1密码错误，返回2成功
int DataBase::login(std::string name, std::string pass)
{
    MYSQL_ROW row; //char** 二维数组，存放一条条记录

     //查询数据
    mysql_query(&mysql, "SELECT * from userInfo");
    //获取结果集
    res = mysql_store_result(&mysql);
    //显示数据
    //给ROW赋值，判断ROW是否为空，不为空就比对用户数据。
    while (row = mysql_fetch_row(res))
    {
        //找到对应用户名
        if (row[0] == name)
        {
            //密码正确
            if (row[1] == pass)
                return 2;
            //密码错误
            else  return 1;

        }
    }

    return 0; //未找到用户
}

//注册，返回是否注册成功，不成功则是用户已存在
bool DataBase::reg(string name, string pass)
{
    MYSQL_ROW row; //char** 二维数组，存放一条条记录

     //查询数据
    mysql_query(&mysql, "SELECT * from userInfo");
    //获取结果集
    res = mysql_store_result(&mysql);
    //显示数据
    //给ROW赋值，判断ROW是否为空，不为空就比对用户数据。
    while (row = mysql_fetch_row(res))
    {
        if (row[0] == name)
            return false; //用户已存在
    }

    //用户名未被占用，创建一条新数据
    string s1 = "insert into userInfo values(";
    string s2 = s1 + "'" + name + "'" + ',' + "'" + pass + "','0','0','0','0','0','0','0');";

    char query[1024];
    strcpy_s(query, s2.c_str());
    cout << query << endl;
    if (mysql_query(&mysql, query) != 0)
    {
        cout << "添加失败" << endl;
        return false;
    }
    else 
        cout << "添加成功" << endl;
       
    

    return true; //添加成功
}

//获取用户关卡数的分数，1-6为闯关模式步数，7为竞速模式分数;返回0则是暂无记录
int DataBase::getScore(int num, std::string name)
{
    MYSQL_ROW row; //char** 二维数组，存放一条条记录

      //查询数据
    mysql_query(&mysql, "SELECT * from userInfo");
    //获取结果集
    res = mysql_store_result(&mysql);
    //显示数据
    //给ROW赋值，判断ROW是否为空，不为空就比对用户数据。
    while (row = mysql_fetch_row(res))
    {
        //找到对应用户名
        if (row[0] == name)
        {
            //返回对应关卡最少步数或得分
            return atoi(row[num + 1]);
        }
    }

    return 0;
}


//设置用户关卡分数或步数
bool DataBase::setScore(int num, int score, string name)
{
    string s0 = "score" + std::to_string(num);
    string s1 = "update userInfo set " + s0 + " = ";
    string s2 = " where name = ";
    string s3 = s1 + std::to_string(score) + s2 + "'" + name + "';";
    cout << s3 << endl;

    char sql[1024];

    strcpy_s(sql, s3.c_str());

    if (mysql_query(&mysql, sql) != 0)
    {
        cout << "更新失败" << endl;
        return false;
    }

    return true; //修改成功
}


//析构函数，释放资源
DataBase::~DataBase()
{
    mysql_free_result(res);  //释放一个结果集合使用的内存。
    mysql_close(&mysql);	 //关闭一个服务器连接。

}


//获得指定关卡的排行，返回排行榜数组（可能无序）
vector<node> DataBase::getRank(int num)
{
    //存放排行的向量
    vector<node> rank;
    //查询对应排行榜的表
    MYSQL_ROW row; //char** 二维数组，存放一条条记录
    bool flag = false; //排行榜为空时为false

     //查询数据
    string s = "SELECT * from rank" + std::to_string(num);
    mysql_query(&mysql, s.c_str());
    //获取结果集
    res = mysql_store_result(&mysql);

    //显示数据
    //给ROW赋值，判断ROW是否为空，不为空就压入vector
    while (row = mysql_fetch_row(res))
    {
        flag = true;
        node temp;
        temp.name = row[0]; //获取昵称
        temp.score = atoi(row[1]); //获取分值或步数
        rank.push_back(temp); //加入rank
    }

    //排行榜为空，直接返回空向量
    if (!flag)
        return rank;

    //全部压入rank，排序
    this->sort(&rank, num);

    //测试用，打印
    cout << "第" << num << "关" << endl;
    for (int i = 0; i < rank.size(); i++)
    {
        cout << rank.at(i).name << "  " << rank.at(i).score << endl;
    }

    //返回排序后的vector
    return rank;
}


//给结构体数组排序，1-6关升序排，第七关降序
void DataBase::sort(vector<node>* rank, int num)
{
    for (int i = 0; i < rank->size() - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < rank->size(); j++)
        {
            //只有第七关降序排
            if (num == 7) {
                if (rank->at(j).score > rank->at(k).score)
                    k = j;
            }
            else
            {
                if (rank->at(j).score < rank->at(k).score)
                    k = j;
            }

        }
        if (k != i)
        {
            //交换
            string name = rank->at(k).name;
            int y = rank->at(k).score;
            rank->at(k).score = rank->at(i).score;
            rank->at(k).name = rank->at(i).name;
            rank->at(i).score = y;
            rank->at(i).name = name;
        }
    }
    cout << "sort" << endl;
    for (int i = 0; i < rank->size(); i++)
    {
        cout << rank->at(i).name << "  " << rank->at(i).score << endl;
    }

}


//判断能否进排行榜，如果能，要更新数据库排行榜内容
bool DataBase::judgeRank(int num, int score, string name)
{
    //先创建一个用户排行结点
    node nn;
    nn.name = name;
    nn.score = score;

    vector<node> sorted = getRank(num); //获取有序的排行榜
    //如果排行榜人没有满，直接加
    if (sorted.size() < 10)
        sorted.push_back(nn);

    //如果人满了，和最后一名比较
    //第7关，比最后一名分数高，进榜
    else if (num == 7)
    {
        //分数更高，把最后一名顶替
        if (score > sorted.at(9).score)
        {
            sorted.at(9).score = score;
            sorted.at(9).name = name;
        }
        else  return false; //不能进榜
    }
    //前六关，比最后一名步数少就进榜
    else
    {
        //步数更少，把最后一名顶替
        if (score < sorted.at(9).score)
        {
            sorted.at(9).score = score;
            sorted.at(9).name = name;
        }
        else  return false; //不能进榜
    }



    //可以进榜，更新数据库内排行榜信息
    //首先把原来表内容清空
    string query = "truncate table rank" + to_string(num);
    if (mysql_query(&mysql, query.c_str()))        //执行SQL语句  
        printf("Query failed (%s)\n", mysql_error(&mysql));
    else
        printf("success\n");

    //然后再把新内容写入
    string s1 = "insert into rank" + to_string(num) + " values(";

    for (int u = 0; u < sorted.size(); u++)
    {
        //mysql语句
        string s2 = s1 + "'" + sorted.at(u).name + "','" + to_string(sorted.at(u).score) + "');";
        //执行语句
        mysql_query(&mysql, s2.c_str());
    }

    return true;
}


//记录用户邮箱
void DataBase::mail(string name, string mail)
{
    string s1 = "insert into userEmail values(";
    string s2 = s1 + "'" + name + "'" + ',' + "'" + mail + "');";

    char query[1024];
    strcpy_s(query, s2.c_str());
    cout << query << endl;
    if (mysql_query(&mysql, query) != 0)
    {
        cout << "添加失败" << endl;
    }
    else cout << "添加成功" << endl;
}


//获取指定用户邮箱
string DataBase::getMail(string name)
{
    MYSQL_ROW row; //char** 二维数组，存放一条条记录

      //查询数据
    mysql_query(&mysql, "SELECT * from userEmail");
    //获取结果集
    res = mysql_store_result(&mysql);
    //显示数据
    //给ROW赋值，判断ROW是否为空，不为空就比对用户数据。
    while (row = mysql_fetch_row(res))
    {
        //找到对应用户名
        if (row[0] == name)
        {
            //返回用户邮箱
            return row[1];
        }
    }
    return ""; //返回空字符串则昵称不存在
}


//修改用户密码
bool DataBase::changePass(string name, string newPass)
{
    string s1 = "update userInfo set password = "+newPass;
    string s2 = " where name = ";
    string s3 = s1 + s2 + "'" + name + "';";
   

    char sql[1024];

    strcpy_s(sql, s3.c_str());

    if (mysql_query(&mysql, sql) != 0)
    {
        cout << "更新失败" << endl;
        return false;
    }

    return true; //修改成功
}