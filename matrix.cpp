#include "matrix.h"

#include <utility>
#include <stdexcept>


linalg::Matrix::Matrix(size_t rows, size_t cols) {
    m_ptr = new double[rows * cols];
    for (size_t i = 0; i < rows * cols; ++i) {
        m_ptr[i] = double();
    }
    m_rows = rows;
    m_columns = cols;
    m_capacity = rows * cols;
}

linalg::Matrix::Matrix(const Matrix &matrix) {
    m_ptr = new double[matrix.m_rows * matrix.m_columns];
    for (size_t i = 0; i < matrix.m_rows * matrix.m_columns; ++i) {
        m_ptr[i] = matrix.m_ptr[i];
    }
    m_rows = matrix.m_rows;
    m_columns = matrix.m_columns;
    m_capacity = m_rows * m_columns;
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list_of_lists) {
    size_t rows = list_of_lists.size();
    size_t columns = list_of_lists.begin()->size();
    double *ptr = new double[rows * columns];
    size_t i = 0;
    for (std::initializer_list<double> list: list_of_lists) {
        if (list.size() != columns) {
            delete[] ptr;
            throw std::runtime_error("Incorrect initialization");
        }
        for (double el: list) {
            ptr[i] = el;
            ++i;
        }
    }
    m_rows = rows;
    m_columns = columns;
    m_capacity = m_rows * m_columns;
    m_ptr = ptr;
}

linalg::Matrix::Matrix(std::initializer_list<double> list) {
    m_ptr = new double[list.size()];
    size_t i = 0;
    for (double el: list) {
        m_ptr[i] = el;
        ++i;
    }
    m_rows = list.size();
    m_columns = 1;
    m_capacity = m_rows;
}

linalg::Matrix &linalg::Matrix::operator=(const Matrix &matrix) {
    double *tmp_ptr = new double[matrix.m_rows * matrix.m_columns];
    for (size_t i = 0; i < matrix.m_rows * matrix.m_columns; ++i) {
        tmp_ptr[i] = matrix.m_ptr[i];
    }
    delete[] m_ptr;
    m_ptr = tmp_ptr;
    m_rows = matrix.m_rows;
    m_columns = matrix.m_columns;
    m_capacity = m_rows * m_columns;
    return *this;
}

linalg::Matrix &linalg::Matrix::operator=(Matrix &&matrix) {
    swap(matrix);
    return *this;
}

void linalg::Matrix::reshape(size_t rows, size_t cols) {
    if (rows * cols != m_rows * m_columns) {
        throw std::runtime_error("Incorrect shape");
    }
    m_rows = rows;
    m_columns = cols;
}

void linalg::Matrix::reserve(size_t n) {
    if (m_rows * m_columns >= n) {
        return;
    }
    double *tmp_ptr = new double[n];
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        tmp_ptr[i] = m_ptr[i];
    }
    delete[] m_ptr;
    m_ptr = tmp_ptr;
    m_capacity = n;
}

void linalg::Matrix::shrink_to_fit() {
    if (m_capacity == m_rows * m_columns) {
        return;
    }
    double *tmp_ptr = new double[m_rows * m_columns];
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        tmp_ptr[i] = m_ptr[i];
    }
    delete[] m_ptr;
    m_ptr = tmp_ptr;
    m_capacity = m_rows * m_columns;
}

void linalg::Matrix::swap(linalg::Matrix &matrix) {
    std::swap(m_ptr, matrix.m_ptr);
    std::swap(m_rows, matrix.m_rows);
    std::swap(m_columns, matrix.m_columns);
    std::swap(m_capacity, matrix.m_capacity);
}


