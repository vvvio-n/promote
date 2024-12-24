#include <iostream>
#include "xiangliang.h"
#include <limits>

int main() {
    try {
        // ���Թ��캯������������
        Vector<int> vec1(5, 1);
        std::cout << "���Թ��캯������������ " <<  std::endl;
        std::cout << "vec1: " << vec1 << std::endl;

        // �������������
        Vector<double> vec2;
        std::cout << "������������� " <<  std::endl;
        std::cout << "������vec2��Ԫ�أ��ÿո�ָ�����" << std::endl;
        std::cin >> vec2;
        std::cout << "vec2: " << vec2 << std::endl;
        std::cout << "vec2��ά�� " << vec2.size() << std::endl;

        // ���Լӷ�������ͼӷ���ֵ�����
        Vector<int> vec3(3, 2);
        Vector<int> vec4(3, 3);
        Vector<int> vec5 = vec3 + vec4;
        std::cout << "���Լӷ�������ͼӷ���ֵ�����" << std::endl;
        std::cout << "vec3:" << vec3 << std::endl;
        std::cout << "vec4: " << vec4 << std::endl;
        std::cout << "vec3 + vec4 = vec5: " << vec5 << std::endl;
        vec3 += vec4;
        std::cout << "vec3 += vec4: " << vec3 << std::endl;

        // ������ȺͲ��������
        std::cout << "������ȺͲ����������" << std::endl;
        if (vec3 == vec5) {
            std::cout << "vec3 ���� vec5" << std::endl;
        } else {
            std::cout << "vec3 ������ vec5" << std::endl;
        }
        if (vec4 != vec5) {
            std::cout << "vec4 ������ vec5" << std::endl;
        } else {
            std::cout << "vec4 ���� vec5" << std::endl;
        }
        // �����쳣����ά����ͬ��
        std::cout << "�����쳣����ά����ͬ��" << std::endl;
        Vector<int> vec6(2, 1);
        // Vector<int> vec7 = vec6 + vec1; // �⽫�׳��쳣
        std::cout << "vec6: " << vec6 << std::endl;
        std::cout << "����vec6+vec1: "<< std::endl;
        try {
            Vector<int> vec7 = vec6 + vec1;
        } catch (const std::invalid_argument& e) {
            std::cerr << "�쳣��" << e.what() << std::endl;
        }

        // �����쳣�����±�Խ�磩
        std::cout << "�����쳣�����±�Խ�磩" << std::endl;
        try {
            std::cout << "vec1[5] = " << vec1[5] << std::endl; // �⽫�׳��쳣
        } catch (const std::out_of_range& e) {
            std::cerr << "�쳣��" << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "δ������쳣��" << e.what() << std::endl;
    }

    return 0;
}
