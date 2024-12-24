//main.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<string>
#include<fstream>
#include"User.h"
#include <cctype>


bool isValidPassword(const char* password) {

    bool hasLetter = false;
    bool hasDigit = false;
    bool hasOtherSymbol = false;

    // 检查密码长度
    int length = strlen(password);
    if (length < 8) {
        std::cout << "密码必须至少包含8个字符。" << std::endl;
        return false;
    }



    // 遍历密码字符，检查是否包含字母和数字，同时检查是否有乱码（空格或非字母数字字符）
    for (size_t i = 0; i < strlen(password); ++i) {
        char c = password[i];
        if (std::isalpha(c)) {
            hasLetter = true;
        }
        else if (std::isdigit(c)) {
            hasDigit = true;
        }
      /* else if (c == ' ') {
            std::cout << "密码不能包含空格。" << std::endl;
            return false;
        }*/
        else {
            hasOtherSymbol = true;
            break;
        }
        }

        // 检查是否同时包含字母和数字且没有其他符号
    if (!hasLetter || !hasDigit || hasOtherSymbol) {
        std::cout << "密码必须同时包含字母和数字，且不能包含其他符号。" << std::endl;
        return false;
    }

    return true;

}

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件"<< std::endl;
        return false;
    }
    // 将文件指针定位到文件末尾
    file.seekg(0, std::ios::end);

    // 获取文件的当前位置，即文件的大小
    bool empty = (file.tellg() == 0);

    // 关闭文件
    file.close();

    return empty;
}



void KATest();

int main()
{
    static int num=0;

    while (true) {
        ++num;
        int choice;
        SavePassword password1;
        SavePassword password2;
        cout << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "|           欢迎进入登陆界面             |\n" << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "|               请选择功能               |\n" << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "|              1 注册账户                |\n" << endl;
        cout << "|              2 登录账户                |\n" << endl;
        cout << "|              3 修改账户                |\n" << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "我要：";
        std::cin >> choice;
        cout << endl << endl;
        if (choice <= 0)    break;

        switch (choice)
        {

        case 1:
            while (true)
            {
                if (num == 1) {
                cout << "请设置密码：" << endl;
              try{
                  std::cin >> password1;
                  if (strlen(password1.c_str()) > 80) {
                      throw PasswordLengthExceededException();}
                  while (!isValidPassword(password1.c_str()))
                {
                    cout << "请重新输入您的密码: ";
                    std::cin >> password1;
                    if (strlen(password1.c_str()) > 80) {
                        throw PasswordLengthExceededException();
                    }
                }
                cout << "请再次输入设置的密码：" << endl;
                std::cin >> password2;
                if (strlen(password2.c_str()) > 80) {
                    throw PasswordLengthExceededException();
                }
                if (password1 == password2) {
                    cout << "密码设置成功！" << endl;
                    password1.ManagePassword();
                    break;
                }
                else {
                    cout << "两次输入的密码不相同，请重新设置。" << endl;
                }
                }
              catch (const PasswordLengthExceededException& e) {
                  cout << e.what() << std::endl;
                  }
                }
                else{
                string filename = "pwd.txt";
                if (isFileEmpty(filename)){
                cout << "请设置密码：" << endl;
              try{
                  std::cin >> password1;
                  if (strlen(password1.c_str()) > 80) {
                      throw PasswordLengthExceededException();
                  }

                  while (!isValidPassword(password1.c_str()))
                {
                    cout << "请重新输入您的密码: ";
                    std::cin >> password1;
                    if (strlen(password1.c_str()) > 80) {
                        throw PasswordLengthExceededException();
                    }
                }
                cout << "请再次输入设置的密码：" << endl;
                std::cin >> password2;
                if (strlen(password2.c_str()) > 80) {
                    throw PasswordLengthExceededException();
                }
                if (password1 == password2) {
                    cout << "密码设置成功！" << endl;
                    password1.ManagePassword();
                    break;
                }
                else {
                    cout << "两次输入的密码不相同，请重新设置。" << endl;
                }
                }
              catch (const PasswordLengthExceededException& e) {
                  cout << e.what() << std::endl;
                  }
                }
                  else{
                    cout<<"已设置过密码不能重复设置"<<endl;
                    break;
                  }
                }
    }
            break;

        case 2:
            cout << "请输入密码" << endl;
            password1.InputPassword();
            break;

        case 3:
            cout << "修改密码" << endl;
            string str;
            std::cin >> str;
            const char* pd = str.c_str();
            password1 = pd;
            password1.ManagePassword();
            cout<<"修改密码成功"<<endl;
            break;

        }
    }

    return 0;
}
