// xiangliang.cpp
#include "xiangliang.h"

// Ĭ�Ϲ��캯������ʼ��ָ����С��ֵ������
//template <typename T>
//Vector<T>::Vector(size_t size, const T& value) : elements(size, value) {}

// ʹ�ó�ʼ���б�Ĺ��캯��
//template <typename T>
//  Vector<T>::Vector(const std::initializer_list<T>& init) : elements(init) {}

// ��������
template <typename T>
Vector<T>::~Vector() {}

// ���ƹ��캯��
template <typename T>
Vector<T>::Vector(const Vector& other) : elements(other.elements) {}

// ���Ƹ�ֵ�����
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        elements = other.elements;
    }
    return *this;
}

// ��ȡ������С
template <typename T>
size_t Vector<T>::size() const {
    return elements.size();
}

// ��������Ƿ�Ϊ��
template <typename T>
bool Vector<T>::isEmpty() const {
    return elements.empty();
}

// �±���������ṩ��Ԫ�صķ���
template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= elements.size()) {
        throw std::out_of_range("����������Χ");
    }
    return elements[index];
}

// �����±���������ṩ��Ԫ�ص�ֻ������
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= elements.size()) {
        throw std::out_of_range("����������Χ");
    }
    return elements[index];
}

// �����ӷ��������ʵ�������ļӷ�
template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("������С������ͬ�������");
    }
    for (size_t i = 0; i < elements.size(); ++i) {
        elements[i] += other.elements[i];
    }
    return *this;
}

// �����ӷ���������������������ĺ�
template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    Vector<T> result = *this;
    result += other;
    return result;
}

// ���������������ڴ�ӡ��������
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i < v.size() - 1) os << " ";
    }
    return os;
}
