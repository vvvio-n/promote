
//user.h
#define _CRT_SECURE_NO_WARNINGS
#ifndef USER_H
#define USER_H
# include<string>
#include<iostream>
using namespace std;


class SavePassword {                                                      //��������
public:
    SavePassword();
    SavePassword(const char* ppassword);
    SavePassword(const SavePassword& pd);
    ~SavePassword();
    SavePassword& operator= (const char* pd);
    SavePassword& operator= (const SavePassword& pd);
    friend istream& operator>>(istream& cin, SavePassword& password);     //pstring��˽�еģ�������Ҫ������Ԫ����
    friend ostream& operator<<(ostream& cout, SavePassword& password);
    bool operator==(const SavePassword& password);
    bool verifyPassword(const char* inputPassword);
    const char* c_str() const;
    void ManagePassword();
    void InputPassword();
private:
    char* pstring;          //�ַ�����
    int m_size;             //�ַ�������
    char pwd[80];

};
class PasswordLengthExceededException : public std::exception {
public:
    const char* what() const noexcept override {
        return "���볤�Ȳ��ܳ��� 80 ���ַ���";
    }
};

class InsufficientMemoryException : public std::exception {
public:
    const char* what() const noexcept override {
        return "�ڴ����ʧ�ܡ�";
    }
};

#endif // USER_H_INCLUDED
