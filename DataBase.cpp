#pragma execution_character_set("utf-8")

#include "DataBase.h"
using namespace std;
User DataBase::player = User();
//������
DataBase::DataBase()
{
    cout << "gouzao" << endl;
    this->connect();
}

//�������ݿ�
void DataBase::connect()
{
    //��ʼ�����ݿ�
    mysql_init(&mysql);
    //���ñ��뷽ʽ
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    cout << "connect" << endl;
    //�������ݿ�
    //�ж��������ʧ�ܾͰ�����ʧ�ܵ���Ϣ��ʾ�������ý��ж�Ӧ�޸ġ�
    // mysql_real_connect������2.��ַ 3.mysql�û��� 4.mysql���� 5.���ݿ����� 6.�˿ں�
    if (mysql_real_connect(&mysql, "175.24.96.32", "commonuser", "commonuser", "common", 3306, NULL, 0) == NULL) {
        cout << (mysql_error(&mysql));
    }
    else cout << "successfully connected!" << endl;

}


//��¼���ȶ��û������룻����0δ�ҵ��û���������1������󣬷���2�ɹ�
int DataBase::login(std::string name, std::string pass)
{
    MYSQL_ROW row; //char** ��ά���飬���һ������¼

     //��ѯ����
    mysql_query(&mysql, "SELECT * from userInfo");
    //��ȡ�����
    res = mysql_store_result(&mysql);
    //��ʾ����
    //��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վͱȶ��û����ݡ�
    while (row = mysql_fetch_row(res))
    {
        //�ҵ���Ӧ�û���
        if (row[0] == name)
        {
            //������ȷ
            if (row[1] == pass)
                return 2;
            //�������
            else  return 1;

        }
    }

    return 0; //δ�ҵ��û�
}

//ע�ᣬ�����Ƿ�ע��ɹ������ɹ������û��Ѵ���
bool DataBase::reg(string name, string pass)
{
    MYSQL_ROW row; //char** ��ά���飬���һ������¼

     //��ѯ����
    mysql_query(&mysql, "SELECT * from userInfo");
    //��ȡ�����
    res = mysql_store_result(&mysql);
    //��ʾ����
    //��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վͱȶ��û����ݡ�
    while (row = mysql_fetch_row(res))
    {
        if (row[0] == name)
            return false; //�û��Ѵ���
    }

    //�û���δ��ռ�ã�����һ��������
    string s1 = "insert into userInfo values(";
    string s2 = s1 + "'" + name + "'" + ',' + "'" + pass + "','0','0','0','0','0','0','0');";

    char query[1024];
    strcpy_s(query, s2.c_str());
    cout << query << endl;
    if (mysql_query(&mysql, query) != 0)
    {
        cout << "���ʧ��" << endl;
        return false;
    }
    else 
        cout << "��ӳɹ�" << endl;
       
    

    return true; //��ӳɹ�
}

//��ȡ�û��ؿ����ķ�����1-6Ϊ����ģʽ������7Ϊ����ģʽ����;����0�������޼�¼
int DataBase::getScore(int num, std::string name)
{
    MYSQL_ROW row; //char** ��ά���飬���һ������¼

      //��ѯ����
    mysql_query(&mysql, "SELECT * from userInfo");
    //��ȡ�����
    res = mysql_store_result(&mysql);
    //��ʾ����
    //��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վͱȶ��û����ݡ�
    while (row = mysql_fetch_row(res))
    {
        //�ҵ���Ӧ�û���
        if (row[0] == name)
        {
            //���ض�Ӧ�ؿ����ٲ�����÷�
            return atoi(row[num + 1]);
        }
    }

    return 0;
}


//�����û��ؿ���������
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
        cout << "����ʧ��" << endl;
        return false;
    }

    return true; //�޸ĳɹ�
}


//�����������ͷ���Դ
DataBase::~DataBase()
{
    mysql_free_result(res);  //�ͷ�һ���������ʹ�õ��ڴ档
    mysql_close(&mysql);	 //�ر�һ�����������ӡ�

}


//���ָ���ؿ������У��������а����飨��������
vector<node> DataBase::getRank(int num)
{
    //������е�����
    vector<node> rank;
    //��ѯ��Ӧ���а�ı�
    MYSQL_ROW row; //char** ��ά���飬���һ������¼
    bool flag = false; //���а�Ϊ��ʱΪfalse

     //��ѯ����
    string s = "SELECT * from rank" + std::to_string(num);
    mysql_query(&mysql, s.c_str());
    //��ȡ�����
    res = mysql_store_result(&mysql);

    //��ʾ����
    //��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վ�ѹ��vector
    while (row = mysql_fetch_row(res))
    {
        flag = true;
        node temp;
        temp.name = row[0]; //��ȡ�ǳ�
        temp.score = atoi(row[1]); //��ȡ��ֵ����
        rank.push_back(temp); //����rank
    }

    //���а�Ϊ�գ�ֱ�ӷ��ؿ�����
    if (!flag)
        return rank;

    //ȫ��ѹ��rank������
    this->sort(&rank, num);

    //�����ã���ӡ
    cout << "��" << num << "��" << endl;
    for (int i = 0; i < rank.size(); i++)
    {
        cout << rank.at(i).name << "  " << rank.at(i).score << endl;
    }

    //����������vector
    return rank;
}


//���ṹ����������1-6�������ţ����߹ؽ���
void DataBase::sort(vector<node>* rank, int num)
{
    for (int i = 0; i < rank->size() - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < rank->size(); j++)
        {
            //ֻ�е��߹ؽ�����
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
            //����
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


//�ж��ܷ�����а�����ܣ�Ҫ�������ݿ����а�����
bool DataBase::judgeRank(int num, int score, string name)
{
    //�ȴ���һ���û����н��
    node nn;
    nn.name = name;
    nn.score = score;

    vector<node> sorted = getRank(num); //��ȡ��������а�
    //������а���û������ֱ�Ӽ�
    if (sorted.size() < 10)
        sorted.push_back(nn);

    //��������ˣ������һ���Ƚ�
    //��7�أ������һ�������ߣ�����
    else if (num == 7)
    {
        //�������ߣ������һ������
        if (score > sorted.at(9).score)
        {
            sorted.at(9).score = score;
            sorted.at(9).name = name;
        }
        else  return false; //���ܽ���
    }
    //ǰ���أ������һ�������پͽ���
    else
    {
        //�������٣������һ������
        if (score < sorted.at(9).score)
        {
            sorted.at(9).score = score;
            sorted.at(9).name = name;
        }
        else  return false; //���ܽ���
    }



    //���Խ��񣬸������ݿ������а���Ϣ
    //���Ȱ�ԭ�����������
    string query = "truncate table rank" + to_string(num);
    if (mysql_query(&mysql, query.c_str()))        //ִ��SQL���  
        printf("Query failed (%s)\n", mysql_error(&mysql));
    else
        printf("success\n");

    //Ȼ���ٰ�������д��
    string s1 = "insert into rank" + to_string(num) + " values(";

    for (int u = 0; u < sorted.size(); u++)
    {
        //mysql���
        string s2 = s1 + "'" + sorted.at(u).name + "','" + to_string(sorted.at(u).score) + "');";
        //ִ�����
        mysql_query(&mysql, s2.c_str());
    }

    return true;
}


//��¼�û�����
void DataBase::mail(string name, string mail)
{
    string s1 = "insert into userEmail values(";
    string s2 = s1 + "'" + name + "'" + ',' + "'" + mail + "');";

    char query[1024];
    strcpy_s(query, s2.c_str());
    cout << query << endl;
    if (mysql_query(&mysql, query) != 0)
    {
        cout << "���ʧ��" << endl;
    }
    else cout << "��ӳɹ�" << endl;
}


//��ȡָ���û�����
string DataBase::getMail(string name)
{
    MYSQL_ROW row; //char** ��ά���飬���һ������¼

      //��ѯ����
    mysql_query(&mysql, "SELECT * from userEmail");
    //��ȡ�����
    res = mysql_store_result(&mysql);
    //��ʾ����
    //��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վͱȶ��û����ݡ�
    while (row = mysql_fetch_row(res))
    {
        //�ҵ���Ӧ�û���
        if (row[0] == name)
        {
            //�����û�����
            return row[1];
        }
    }
    return ""; //���ؿ��ַ������ǳƲ�����
}


//�޸��û�����
bool DataBase::changePass(string name, string newPass)
{
    string s1 = "update userInfo set password = "+newPass;
    string s2 = " where name = ";
    string s3 = s1 + s2 + "'" + name + "';";
   

    char sql[1024];

    strcpy_s(sql, s3.c_str());

    if (mysql_query(&mysql, sql) != 0)
    {
        cout << "����ʧ��" << endl;
        return false;
    }

    return true; //�޸ĳɹ�
}