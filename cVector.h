#ifdef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>

// Vector 类模板声明
template<typename T>
class Vector {
public:
    // 默认构造函数
    Vector() = default;

    // 使用初始化列表进行构造
    Vector(std::initializer_list<T> list);

    // 重载 << 运算符，用于输出流
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

    // 重载 >> 运算符，用于输入流
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Vector<U>& vec);

    // 重载 + 运算符，返回新的 Vector 对象
    Vector<T> operator+(const Vector<T>& other) const;

    // 重载 += 运算符，修改当前对象并返回引用
    Vector<T>& operator+=(const Vector<T>& other);

    // 清空 Vector 的方法
    Vector<T>& clear();

private:
    std::vector<T> data;
};

// 函数定义在头文件中，以便模板类正确链接
template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) : data(list) {}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.data.size(); ++i) {
        os << vec.data[i];
        if (i < vec.data.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vec) {
    vec.data.clear();
    T value;
    while (is >> value) {
        vec.data.push_back(value);
    }
    return is;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    Vector<T> result;
    size_t size = std::min(data.size(), other.data.size());
    result.data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = this->data[i] + other.data[i];
    }
    return result;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    size_t size = std::min(data.size(), other.data.size());
    for (size_t i = 0; i < size; ++i) {
        this->data[i] += other.data[i];
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::clear() {
    data.clear();
    return *this;
}

#endif        //VECTOR_H