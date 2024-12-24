// xiangliang.cpp
#include "xiangliang.h"

// 默认构造函数，初始化指定大小和值的向量
//template <typename T>
//Vector<T>::Vector(size_t size, const T& value) : elements(size, value) {}

// 使用初始化列表的构造函数
//template <typename T>
//  Vector<T>::Vector(const std::initializer_list<T>& init) : elements(init) {}

// 析构函数
template <typename T>
Vector<T>::~Vector() {}

// 复制构造函数
template <typename T>
Vector<T>::Vector(const Vector& other) : elements(other.elements) {}

// 复制赋值运算符
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        elements = other.elements;
    }
    return *this;
}

// 获取向量大小
template <typename T>
size_t Vector<T>::size() const {
    return elements.size();
}

// 检查向量是否为空
template <typename T>
bool Vector<T>::isEmpty() const {
    return elements.empty();
}

// 下标运算符，提供对元素的访问
template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= elements.size()) {
        throw std::out_of_range("索引超出范围");
    }
    return elements[index];
}

// 常量下标运算符，提供对元素的只读访问
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= elements.size()) {
        throw std::out_of_range("索引超出范围");
    }
    return elements[index];
}

// 向量加法运算符，实现向量的加法
template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("向量大小必须相同才能相加");
    }
    for (size_t i = 0; i < elements.size(); ++i) {
        elements[i] += other.elements[i];
    }
    return *this;
}

// 向量加法运算符，返回两个向量的和
template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    Vector<T> result = *this;
    result += other;
    return result;
}

// 输出流运算符，用于打印向量内容
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i < v.size() - 1) os << " ";
    }
    return os;
}
