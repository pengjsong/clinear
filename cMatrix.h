// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class Matrix {
public:
    // 默认构造函数
    Matrix();

    // 使用行数和列数进行构造
    Matrix(size_t rows, size_t cols);

    // 使用初始化列表进行构造
    Matrix(std::initializer_list<std::initializer_list<T>> list);

    // 析构函数
    ~Matrix();

    // 拷贝构造函数
    Matrix(const Matrix& other);

    // 移动构造函数
    Matrix(Matrix&& other) noexcept;

    // 拷贝赋值运算符
    Matrix& operator=(const Matrix& other);

    // 移动赋值运算符
    Matrix& operator=(Matrix&& other) noexcept;

    // 重载 << 运算符，用于输出流
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat);

    // 获取行数
    size_t rows() const;

    // 获取列数
    size_t cols() const;

    // 重载 () 运算符用于访问矩阵元素
    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<T> m_data;

    // 释放资源
    void free();
};

// 默认构造函数
template<typename T>
Matrix<T>::Matrix() : m_rows(0), m_cols(0), m_data() {}

// 使用行数和列数进行构造
template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_data(rows * cols) {}

// 使用初始化列表进行构造
template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    m_rows = list.size();
    m_cols = list.begin()->size();
    m_data.reserve(m_rows * m_cols);
    for (const auto& row : list) {
        m_data.insert(m_data.end(), row.begin(), row.end());
    }
}

// 析构函数
template<typename T>
Matrix<T>::~Matrix() {
    free();
}

// 拷贝构造函数
template<typename T>
Matrix<T>::Matrix(const Matrix& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_data(other.m_data) {}

// 移动构造函数
template<typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept : m_rows(other.m_rows), m_cols(other.m_cols), m_data(std::move(other.m_data)) {
    other.m_rows = 0;
    other.m_cols = 0;
}

// 拷贝赋值运算符
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        free();
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = other.m_data;
    }
    return *this;
}

// 移动赋值运算符
template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        free();
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = std::move(other.m_data);
        other.m_rows = 0;
        other.m_cols = 0;
    }
    return *this;
}

// 重载 << 运算符，用于输出流
template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
    for (size_t i = 0; i < mat.m_rows; ++i) {
        for (size_t j = 0; j < mat.m_cols; ++j) {
            os << mat(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

// 获取行数
template<typename T>
size_t Matrix<T>::rows() const {
    return m_rows;
}

// 获取列数
template<typename T>
size_t Matrix<T>::cols() const {
    return m_cols;
}

// 重载 () 运算符用于访问矩阵元素
template<typename T>
T& Matrix<T>::operator()(size_t row, size_t col) {
    if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return m_data[row * m_cols + col];
}

template<typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const {
    if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return m_data[row * m_cols + col];
}

// 释放资源
template<typename T>
void Matrix<T>::free() {
    m_data.clear();
    m_rows = 0;
    m_cols = 0;
}

#endif // MATRIX_H