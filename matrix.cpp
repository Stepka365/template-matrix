#include "matrix.h"

linalg::Matrix::Matrix(size_t rows, size_t cols) {
    m_ptr = new double[rows * cols];
    for (size_t i = 0; i < rows * cols; ++i) {
        m_ptr[i] = double();
    }
    m_rows = rows;
    m_columns = cols;
    m_capacity = rows * cols;
}

void linalg::Matrix::reshape(size_t rows, size_t cols) {
    if (rows * cols != m_rows * m_columns) {
        throw;
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
