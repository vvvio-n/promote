//user.cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include <conio.h>
#include<string>
#include<fstream>
#include<cstring>
#include"User.h"
using namespace std;


SavePassword::SavePassword() {                                     //默认构造函数

    pstring = nullptr;
    m_size = 0;
}

SavePassword::SavePassword(const char* password = "nopassword")    //有参构造函数
{
    cout << "构造" << endl;
    if (password == nullptr)
    {
        throw std::invalid_argument("传入的密码指针不能为 nullptr。");
    }
    try
    {
        this->pstring = new char[strlen(password) + 1];
        strcpy(this->pstring, password);
        this->m_size = strlen(password);
        cout << password << endl;
    }
    catch (const std::bad_alloc& e)
    {
        throw InsufficientMemoryException();
    }
}

SavePassword::SavePassword(const SavePassword& pd)                 //深拷贝构造函数 保证每个对象都有自己的资源空间
{
    try
    {
        this->pstring = new char[strlen(pd.pstring) + 1];
        strcpy(this->pstring, pd.pstring);
        this->m_size = pd.m_size;
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << "内存分配失败：" << e.what() << endl;
        this->pstring = nullptr;
        this->m_size = 0;
    }
}

SavePassword::~SavePassword()                                      //析构函数
{
    cout << "析构" << endl;
    if (this->pstring != NULL)
    {
        delete[] this->pstring;
        this->pstring = NULL;
    }
}


const char* SavePassword::c_str() const
{
    return pstring;
}

SavePassword& SavePassword::operator=(const char* pd)             //重载=运算符   对象=常量字符
{
    if (pstring)
    {
        delete[] pstring;
        pstring = NULL;
    }
    pstring = new char[strlen(pd) + 1];
    strcpy(pstring, pd);
    m_size = strlen(pd);
    return *this;
}

SavePassword& SavePassword::operator= (const SavePassword& pd)      //重载=运算符   对象=对象
{
    if(pstring)
    {
        delete[] pstring;
        pstring = NULL;
    }
     pstring = new char[strlen(pd.pstring)+1];
     strcpy(pstring,pd.pstring);
     m_size = strlen(pd.pstring);
     return *this;
}

bool SavePassword::operator==(const SavePassword& password)        //重载==运算符
{
    if (strcmp(this->pstring, password.pstring) == 0)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& cout, SavePassword& password)        //重载<<运算符
{
    cout << password.pstring;
    return cout;
}

istream& operator>>(istream& cin, SavePassword& password)        //重载>>运算符
{
    if (password.pstring)
    {
        delete[] password.pstring;
        password.pstring = NULL;
    }
    char buf[1024];                           //开辟临时 确保内存分配完成之前不会丢失数据

    char  c = 0;
    int i = 0;
    // 循环直到时间到或用户完成输入
    do
    {
        if (_kbhit())
        {                                         // 检查键盘输入
            c = _getch();                                       // 获取按键
            switch (c)
            {
            case '\b':                                     // 处理退格键
                if (i > 0)
                {
                    cout << c << " " << c << flush;
                    i--;
                }
                break;
            case '\r':                                     // 回车，表示输入结束
                buf[i] = '\0';                             // 在输入的字符串末尾加终止符
                cout << endl;    break;
            case ' ':
                buf[i] = '\0';
                cout << endl;    break;
            default:
                buf[i++] = c;  // 保存字符
                std::cout << "*" << std::flush;  // 打印星号
            }
        }
    } while (i < sizeof(buf) && c != '\r');

    password.pstring = new char[strlen(buf) + 1];
    strcpy(password.pstring, buf);
    password.m_size = strlen(buf);
    cout << password.m_size << endl;

    return cin;
}

void SavePassword::ManagePassword()
{
    ofstream outFile;
    outFile.open("pwd.txt");                  //将密码储存到txt文本中
    if (outFile.is_open()) {
        outFile << pstring << endl;
        outFile.close();
    }
}


bool SavePassword::verifyPassword(const char* inputPassword) {            //检查用户输入的密码和文件里的密码是否相符
    ifstream inputFile("pwd.txt");
    string line;
    while (getline(inputFile, line)) {            //遍历读取所有行
        const char* Line = line.c_str();
        if (strcmp(this->pwd, Line) == 0)
            return true;
    }
    return false;
    // 比较输入的密码和存储的密码
}

void KATest();

void SavePassword::InputPassword()              //模拟登录过程,密码输入到pwd数组中
{
    char  c = 0;
    int i = 0;

    std::cout << "Please enter your password: " << endl;

    // 循环直到时间到或用户完成输入
    do
    {
        if (_kbhit())
        {                                         // 检查键盘输入
            c = _getch();                                       // 获取按键
            switch (c)
            {
            case '\b':                                     // 处理退格键
                if (i > 0)
                {
                    cout << c << " " << c << flush;
                    i--;
                }
                break;
            case '\r':                                     // 回车，表示输入结束
                pwd[i] = '\0';                             // 在输入的字符串末尾加终止符
                cout << endl;    break;
            case ' ':
                pwd[i] = '\0';
                cout << endl;    break;
            default:
                pwd[i++] = c;  // 保存字符
                std::cout << "*" << std::flush;  // 打印星号
            }
        }
    } while (i < sizeof(pwd) && c != '\r');

    pwd[sizeof(pwd) - 1] = '\0';
    //        cout<<pwd<<endl;
    if (verifyPassword(pwd)) {
        cout << "密码正确！" << endl;
        cout<<endl<<endl;
        KATest();
    }
    else {
        cout << "密码错误！" << endl;
    }
}

