#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
template <typename T>
class Vector {
private:
    std::vector<T> elements;

public:
    // 默认构造函数
    Vector() = default;

    // 指定大小和初始值的构造函数
    Vector(size_t size, const T& value = T()) : elements(size, value) {}

    // 使用初始化列表的构造函数
    Vector(const std::initializer_list<T>& init) : elements(init) {}

    // 复制构造函数
    Vector(const Vector& other) : elements(other.elements) {}

    // 移动构造函数
    Vector(Vector&& other) noexcept : elements(std::move(other.elements)) {}

    // 析构函数
    ~Vector() = default;

    // 复制赋值运算符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }

    // 移动赋值运算符
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            elements = std::move(other.elements);
        }
        return *this;
    }

    // 获取向量大小
    size_t size() const {
        return elements.size();
    }

    // 返回维数（与大小相同）
    size_t dimension() const {
        return size();
    }

    // 下标运算符，提供对元素的访问
    T& operator[](size_t index) {
        if (index >= elements.size()) {
            throw std::out_of_range("索引超出范围");
        }
        return elements[index];
    }

    // 常量下标运算符，提供对元素的只读访问
    const T& operator[](size_t index) const {
        if (index >= elements.size()) {
            throw std::out_of_range("索引超出范围");
        }
        return elements[index];
    }

    // 向量加法运算符，实现向量的加法（要求维数相同）
    Vector operator+(const Vector& other) const {
        if (this->size() != other.size()) {
            throw std::invalid_argument("向量维数不同，无法相加");
        }
        Vector result(this->size());
        for (size_t i = 0; i < this->size(); ++i) {
            result[i] = this->elements[i] + other.elements[i];
        }
        return result;
    }

    // 向量加法赋值运算符
    Vector& operator+=(const Vector& other) {
        if (this->size() != other.size()) {
            throw std::invalid_argument("向量维数不同，无法相加");
        }
        for (size_t i = 0; i < this->size(); ++i) {
            this->elements[i] += other.elements[i];
        }
        return *this;
    }

    // 相等运算符
    bool operator==(const Vector& other) const {
        if (this->size() != other.size()) {
            return false;
        }
        for (size_t i = 0; i < this->size(); ++i) {
            if (this->elements[i] != other.elements[i]) {
                return false;
            }
        }
        return true;
    }

    // 不等运算符
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // 友元函数，用于输出流运算符
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            os << v[i];
            if (i < v.size() - 1) os << " ";
        }
        return os;
    }

      // 输入流运算符重载
  friend std::istream& operator>>(std::istream& is, Vector<T>& v) {
    v.elements.clear(); // 清空现有的元素，为新的输入做准备
    T value;            // 用于临时存储从输入流中读取的值

    // 循环读取值，直到输入流结束或遇到错误
    while (is >> value) {
        v.elements.push_back(value); // 将读取的值添加到Vector的elements中

        // 检查下一个字符，如果它不是空白字符，则设置错误状态
        if (is.peek() != ' ' && !is.eof()) {
            is.setstate(std::ios::failbit); // 设置输入流为错误状态
            break; // 退出循环
        }

        // 忽略分隔符
        is.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }

    // 如果输入流因为非文件尾的原因而失败，则清除错误状态并忽略到行尾
    if (is.fail() && !is.eof()) {
        is.clear(); // 清除错误状态
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略剩余输入直到行尾
    }

    return is;
}
};

#endif // VECTOR_TEMPLATE_H
