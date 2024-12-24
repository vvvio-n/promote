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
    // Ĭ�Ϲ��캯��
    Vector() = default;

    // ָ����С�ͳ�ʼֵ�Ĺ��캯��
    Vector(size_t size, const T& value = T()) : elements(size, value) {}

    // ʹ�ó�ʼ���б�Ĺ��캯��
    Vector(const std::initializer_list<T>& init) : elements(init) {}

    // ���ƹ��캯��
    Vector(const Vector& other) : elements(other.elements) {}

    // �ƶ����캯��
    Vector(Vector&& other) noexcept : elements(std::move(other.elements)) {}

    // ��������
    ~Vector() = default;

    // ���Ƹ�ֵ�����
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }

    // �ƶ���ֵ�����
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            elements = std::move(other.elements);
        }
        return *this;
    }

    // ��ȡ������С
    size_t size() const {
        return elements.size();
    }

    // ����ά�������С��ͬ��
    size_t dimension() const {
        return size();
    }

    // �±���������ṩ��Ԫ�صķ���
    T& operator[](size_t index) {
        if (index >= elements.size()) {
            throw std::out_of_range("����������Χ");
        }
        return elements[index];
    }

    // �����±���������ṩ��Ԫ�ص�ֻ������
    const T& operator[](size_t index) const {
        if (index >= elements.size()) {
            throw std::out_of_range("����������Χ");
        }
        return elements[index];
    }

    // �����ӷ��������ʵ�������ļӷ���Ҫ��ά����ͬ��
    Vector operator+(const Vector& other) const {
        if (this->size() != other.size()) {
            throw std::invalid_argument("����ά����ͬ���޷����");
        }
        Vector result(this->size());
        for (size_t i = 0; i < this->size(); ++i) {
            result[i] = this->elements[i] + other.elements[i];
        }
        return result;
    }

    // �����ӷ���ֵ�����
    Vector& operator+=(const Vector& other) {
        if (this->size() != other.size()) {
            throw std::invalid_argument("����ά����ͬ���޷����");
        }
        for (size_t i = 0; i < this->size(); ++i) {
            this->elements[i] += other.elements[i];
        }
        return *this;
    }

    // ��������
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

    // ���������
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // ��Ԫ��������������������
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            os << v[i];
            if (i < v.size() - 1) os << " ";
        }
        return os;
    }

      // ���������������
  friend std::istream& operator>>(std::istream& is, Vector<T>& v) {
    v.elements.clear(); // ������е�Ԫ�أ�Ϊ�µ�������׼��
    T value;            // ������ʱ�洢���������ж�ȡ��ֵ

    // ѭ����ȡֵ��ֱ����������������������
    while (is >> value) {
        v.elements.push_back(value); // ����ȡ��ֵ��ӵ�Vector��elements��

        // �����һ���ַ�����������ǿհ��ַ��������ô���״̬
        if (is.peek() != ' ' && !is.eof()) {
            is.setstate(std::ios::failbit); // ����������Ϊ����״̬
            break; // �˳�ѭ��
        }

        // ���Էָ���
        is.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }

    // �����������Ϊ���ļ�β��ԭ���ʧ�ܣ����������״̬�����Ե���β
    if (is.fail() && !is.eof()) {
        is.clear(); // �������״̬
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ����ʣ������ֱ����β
    }

    return is;
}
};

#endif // VECTOR_TEMPLATE_H
