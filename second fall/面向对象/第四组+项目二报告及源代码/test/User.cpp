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


SavePassword::SavePassword() {                                     //Ĭ�Ϲ��캯��

    pstring = nullptr;
    m_size = 0;
}

SavePassword::SavePassword(const char* password = "nopassword")    //�вι��캯��
{
    cout << "����" << endl;
    if (password == nullptr)
    {
        throw std::invalid_argument("���������ָ�벻��Ϊ nullptr��");
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

SavePassword::SavePassword(const SavePassword& pd)                 //������캯�� ��֤ÿ���������Լ�����Դ�ռ�
{
    try
    {
        this->pstring = new char[strlen(pd.pstring) + 1];
        strcpy(this->pstring, pd.pstring);
        this->m_size = pd.m_size;
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << "�ڴ����ʧ�ܣ�" << e.what() << endl;
        this->pstring = nullptr;
        this->m_size = 0;
    }
}

SavePassword::~SavePassword()                                      //��������
{
    cout << "����" << endl;
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

SavePassword& SavePassword::operator=(const char* pd)             //����=�����   ����=�����ַ�
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

SavePassword& SavePassword::operator= (const SavePassword& pd)      //����=�����   ����=����
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

bool SavePassword::operator==(const SavePassword& password)        //����==�����
{
    if (strcmp(this->pstring, password.pstring) == 0)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& cout, SavePassword& password)        //����<<�����
{
    cout << password.pstring;
    return cout;
}

istream& operator>>(istream& cin, SavePassword& password)        //����>>�����
{
    if (password.pstring)
    {
        delete[] password.pstring;
        password.pstring = NULL;
    }
    char buf[1024];                           //������ʱ ȷ���ڴ�������֮ǰ���ᶪʧ����

    char  c = 0;
    int i = 0;
    // ѭ��ֱ��ʱ�䵽���û��������
    do
    {
        if (_kbhit())
        {                                         // ����������
            c = _getch();                                       // ��ȡ����
            switch (c)
            {
            case '\b':                                     // �����˸��
                if (i > 0)
                {
                    cout << c << " " << c << flush;
                    i--;
                }
                break;
            case '\r':                                     // �س�����ʾ�������
                buf[i] = '\0';                             // ��������ַ���ĩβ����ֹ��
                cout << endl;    break;
            case ' ':
                buf[i] = '\0';
                cout << endl;    break;
            default:
                buf[i++] = c;  // �����ַ�
                std::cout << "*" << std::flush;  // ��ӡ�Ǻ�
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
    outFile.open("pwd.txt");                  //�����봢�浽txt�ı���
    if (outFile.is_open()) {
        outFile << pstring << endl;
        outFile.close();
    }
}


bool SavePassword::verifyPassword(const char* inputPassword) {            //����û������������ļ���������Ƿ����
    ifstream inputFile("pwd.txt");
    string line;
    while (getline(inputFile, line)) {            //������ȡ������
        const char* Line = line.c_str();
        if (strcmp(this->pwd, Line) == 0)
            return true;
    }
    return false;
    // �Ƚ����������ʹ洢������
}

void KATest();

void SavePassword::InputPassword()              //ģ���¼����,�������뵽pwd������
{
    char  c = 0;
    int i = 0;

    std::cout << "Please enter your password: " << endl;

    // ѭ��ֱ��ʱ�䵽���û��������
    do
    {
        if (_kbhit())
        {                                         // ����������
            c = _getch();                                       // ��ȡ����
            switch (c)
            {
            case '\b':                                     // �����˸��
                if (i > 0)
                {
                    cout << c << " " << c << flush;
                    i--;
                }
                break;
            case '\r':                                     // �س�����ʾ�������
                pwd[i] = '\0';                             // ��������ַ���ĩβ����ֹ��
                cout << endl;    break;
            case ' ':
                pwd[i] = '\0';
                cout << endl;    break;
            default:
                pwd[i++] = c;  // �����ַ�
                std::cout << "*" << std::flush;  // ��ӡ�Ǻ�
            }
        }
    } while (i < sizeof(pwd) && c != '\r');

    pwd[sizeof(pwd) - 1] = '\0';
    //        cout<<pwd<<endl;
    if (verifyPassword(pwd)) {
        cout << "������ȷ��" << endl;
        cout<<endl<<endl;
        KATest();
    }
    else {
        cout << "�������" << endl;
    }
}

