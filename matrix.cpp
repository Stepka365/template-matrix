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

linalg::Matrix::Matrix(const linalg::Matrix &matrix) {
    m_ptr = new double[matrix.m_rows * matrix.m_columns];
    for (size_t i = 0; i < matrix.m_rows * matrix.m_columns; ++i) {
        m_ptr[i] = matrix.m_ptr[i];
    }
    m_rows = matrix.m_rows;
    m_columns = matrix.m_columns;
    m_capacity = m_rows * m_columns;
}

linalg::Matrix &linalg::Matrix::operator=(const linalg::Matrix &matrix) {
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


