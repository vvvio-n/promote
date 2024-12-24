#include <iostream>
#include "xiangliang.h"
#include <limits>

int main() {
    try {
        // 测试构造函数和输出运算符
        Vector<int> vec1(5, 1);
        std::cout << "测试构造函数和输出运算符 " <<  std::endl;
        std::cout << "vec1: " << vec1 << std::endl;

        // 测试输入运算符
        Vector<double> vec2;
        std::cout << "测试输入运算符 " <<  std::endl;
        std::cout << "请输入vec2的元素（用空格分隔）：" << std::endl;
        std::cin >> vec2;
        std::cout << "vec2: " << vec2 << std::endl;
        std::cout << "vec2的维度 " << vec2.size() << std::endl;

        // 测试加法运算符和加法赋值运算符
        Vector<int> vec3(3, 2);
        Vector<int> vec4(3, 3);
        Vector<int> vec5 = vec3 + vec4;
        std::cout << "测试加法运算符和加法赋值运算符" << std::endl;
        std::cout << "vec3:" << vec3 << std::endl;
        std::cout << "vec4: " << vec4 << std::endl;
        std::cout << "vec3 + vec4 = vec5: " << vec5 << std::endl;
        vec3 += vec4;
        std::cout << "vec3 += vec4: " << vec3 << std::endl;

        // 测试相等和不等运算符
        std::cout << "测试相等和不等运算符：" << std::endl;
        if (vec3 == vec5) {
            std::cout << "vec3 等于 vec5" << std::endl;
        } else {
            std::cout << "vec3 不等于 vec5" << std::endl;
        }
        if (vec4 != vec5) {
            std::cout << "vec4 不等于 vec5" << std::endl;
        } else {
            std::cout << "vec4 等于 vec5" << std::endl;
        }
        // 测试异常处理（维数不同）
        std::cout << "测试异常处理（维数不同）" << std::endl;
        Vector<int> vec6(2, 1);
        // Vector<int> vec7 = vec6 + vec1; // 这将抛出异常
        std::cout << "vec6: " << vec6 << std::endl;
        std::cout << "计算vec6+vec1: "<< std::endl;
        try {
            Vector<int> vec7 = vec6 + vec1;
        } catch (const std::invalid_argument& e) {
            std::cerr << "异常：" << e.what() << std::endl;
        }

        // 测试异常处理（下标越界）
        std::cout << "测试异常处理（下标越界）" << std::endl;
        try {
            std::cout << "vec1[5] = " << vec1[5] << std::endl; // 这将抛出异常
        } catch (const std::out_of_range& e) {
            std::cerr << "异常：" << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "未捕获的异常：" << e.what() << std::endl;
    }

    return 0;
}
