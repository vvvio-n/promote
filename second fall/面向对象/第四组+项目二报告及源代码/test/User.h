
//user.h
#define _CRT_SECURE_NO_WARNINGS
#ifndef USER_H
#define USER_H
# include<string>
#include<iostream>
using namespace std;


class SavePassword {                                                      //储存密码
public:
    SavePassword();
    SavePassword(const char* ppassword);
    SavePassword(const SavePassword& pd);
    ~SavePassword();
    SavePassword& operator= (const char* pd);
    SavePassword& operator= (const SavePassword& pd);
    friend istream& operator>>(istream& cin, SavePassword& password);     //pstring是私有的，所以需要加上友元声明
    friend ostream& operator<<(ostream& cout, SavePassword& password);
    bool operator==(const SavePassword& password);
    bool verifyPassword(const char* inputPassword);
    const char* c_str() const;
    void ManagePassword();
    void InputPassword();
private:
    char* pstring;          //字符数组
    int m_size;             //字符串长度
    char pwd[80];

};
class PasswordLengthExceededException : public std::exception {
public:
    const char* what() const noexcept override {
        return "密码长度不能超过 80 个字符。";
    }
};

class InsufficientMemoryException : public std::exception {
public:
    const char* what() const noexcept override {
        return "内存分配失败。";
    }
};

#endif // USER_H_INCLUDED
