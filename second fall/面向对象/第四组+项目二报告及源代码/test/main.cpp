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

    // ������볤��
    int length = strlen(password);
    if (length < 8) {
        std::cout << "����������ٰ���8���ַ���" << std::endl;
        return false;
    }



    // ���������ַ�������Ƿ������ĸ�����֣�ͬʱ����Ƿ������루�ո�����ĸ�����ַ���
    for (size_t i = 0; i < strlen(password); ++i) {
        char c = password[i];
        if (std::isalpha(c)) {
            hasLetter = true;
        }
        else if (std::isdigit(c)) {
            hasDigit = true;
        }
      /* else if (c == ' ') {
            std::cout << "���벻�ܰ����ո�" << std::endl;
            return false;
        }*/
        else {
            hasOtherSymbol = true;
            break;
        }
        }

        // ����Ƿ�ͬʱ������ĸ��������û����������
    if (!hasLetter || !hasDigit || hasOtherSymbol) {
        std::cout << "�������ͬʱ������ĸ�����֣��Ҳ��ܰ����������š�" << std::endl;
        return false;
    }

    return true;

}

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�"<< std::endl;
        return false;
    }
    // ���ļ�ָ�붨λ���ļ�ĩβ
    file.seekg(0, std::ios::end);

    // ��ȡ�ļ��ĵ�ǰλ�ã����ļ��Ĵ�С
    bool empty = (file.tellg() == 0);

    // �ر��ļ�
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
        cout << "|           ��ӭ�����½����             |\n" << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "|               ��ѡ����               |\n" << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "|              1 ע���˻�                |\n" << endl;
        cout << "|              2 ��¼�˻�                |\n" << endl;
        cout << "|              3 �޸��˻�                |\n" << endl;
        cout << "------------------------------------------\n" << endl;
        cout << "��Ҫ��";
        std::cin >> choice;
        cout << endl << endl;
        if (choice <= 0)    break;

        switch (choice)
        {

        case 1:
            while (true)
            {
                if (num == 1) {
                cout << "���������룺" << endl;
              try{
                  std::cin >> password1;
                  if (strlen(password1.c_str()) > 80) {
                      throw PasswordLengthExceededException();}
                  while (!isValidPassword(password1.c_str()))
                {
                    cout << "������������������: ";
                    std::cin >> password1;
                    if (strlen(password1.c_str()) > 80) {
                        throw PasswordLengthExceededException();
                    }
                }
                cout << "���ٴ��������õ����룺" << endl;
                std::cin >> password2;
                if (strlen(password2.c_str()) > 80) {
                    throw PasswordLengthExceededException();
                }
                if (password1 == password2) {
                    cout << "�������óɹ���" << endl;
                    password1.ManagePassword();
                    break;
                }
                else {
                    cout << "������������벻��ͬ�����������á�" << endl;
                }
                }
              catch (const PasswordLengthExceededException& e) {
                  cout << e.what() << std::endl;
                  }
                }
                else{
                string filename = "pwd.txt";
                if (isFileEmpty(filename)){
                cout << "���������룺" << endl;
              try{
                  std::cin >> password1;
                  if (strlen(password1.c_str()) > 80) {
                      throw PasswordLengthExceededException();
                  }

                  while (!isValidPassword(password1.c_str()))
                {
                    cout << "������������������: ";
                    std::cin >> password1;
                    if (strlen(password1.c_str()) > 80) {
                        throw PasswordLengthExceededException();
                    }
                }
                cout << "���ٴ��������õ����룺" << endl;
                std::cin >> password2;
                if (strlen(password2.c_str()) > 80) {
                    throw PasswordLengthExceededException();
                }
                if (password1 == password2) {
                    cout << "�������óɹ���" << endl;
                    password1.ManagePassword();
                    break;
                }
                else {
                    cout << "������������벻��ͬ�����������á�" << endl;
                }
                }
              catch (const PasswordLengthExceededException& e) {
                  cout << e.what() << std::endl;
                  }
                }
                  else{
                    cout<<"�����ù����벻���ظ�����"<<endl;
                    break;
                  }
                }
    }
            break;

        case 2:
            cout << "����������" << endl;
            password1.InputPassword();
            break;

        case 3:
            cout << "�޸�����" << endl;
            string str;
            std::cin >> str;
            const char* pd = str.c_str();
            password1 = pd;
            password1.ManagePassword();
            cout<<"�޸�����ɹ�"<<endl;
            break;

        }
    }

    return 0;
}
