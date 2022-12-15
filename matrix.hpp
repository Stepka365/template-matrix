#pragma once

#include <utility>

template<typename T>
linalg::Matrix<T>::Matrix(size_t rows, size_t cols) {
    T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * rows * cols));
    T *cur_ptr = tmp_ptr;
    try {
        while (cur_ptr != tmp_ptr + rows * cols) {
            new(cur_ptr) T();
            ++cur_ptr;
        }
    } catch (...) {
        for (T *ptr = tmp_ptr; ptr != cur_ptr; ++ptr) {
            ptr->~T();
        }
        delete reinterpret_cast<void *>(tmp_ptr);
        throw;
    }
    m_ptr = tmp_ptr;
    m_rows = rows;
    m_columns = cols;
    m_capacity = rows * cols;
}

template<typename T>
linalg::Matrix<T>::Matrix(const Matrix &matrix) {
    copy_constructor(matrix);
}

template<typename T>
template<typename T2>
linalg::Matrix<T>::Matrix(const Matrix <T2> &matrix) {
    copy_constructor(matrix);
}

template<typename T>
template<typename T2>
void linalg::Matrix<T>::copy_constructor(const Matrix <T2> &matrix) {
    if (matrix.m_rows == 0) return;
    T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * matrix.m_rows * matrix.m_columns));
    T *cur_ptr = tmp_ptr;
    try {
        for (T2 *ptr = matrix.m_ptr; ptr != matrix.m_ptr + matrix.m_rows * matrix.m_columns;
             ++cur_ptr, ++ptr)
            new(cur_ptr) T(*ptr);
    } catch (...) {
        for (T *ptr = tmp_ptr; ptr != cur_ptr; ++ptr) {
            ptr->~T();
        }
        delete reinterpret_cast<void *>(tmp_ptr);
        throw;
    }
    m_ptr = tmp_ptr;
    m_rows = matrix.m_rows;
    m_columns = matrix.m_columns;
    m_capacity = m_rows * m_columns;
}

template<typename T>
template<typename T1>
linalg::Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T1>> list_of_lists) {
    size_t rows = list_of_lists.size();
    size_t columns = list_of_lists.begin()->size();
    T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * rows * columns));
    T *cur_ptr = tmp_ptr;
    try {
        for (std::initializer_list<T1> list: list_of_lists) {
            if (list.size() != columns) {
                throw MatrixInitError("Incorrect initialization");
            }
            for (T1 el: list) {
                new(cur_ptr) T(el);
                ++cur_ptr;
            }
        }
    } catch (...) {
        for (T *ptr = tmp_ptr; ptr != cur_ptr; ++ptr) {
            ptr->~T();
        }
        delete reinterpret_cast<void *>(tmp_ptr);
        throw;
    }
    m_ptr = tmp_ptr;
    m_rows = rows;
    m_columns = columns;
    m_capacity = m_rows * m_columns;
}

template<typename T>
template<typename T1>
linalg::Matrix<T>::Matrix(std::initializer_list<T1> list) {
    T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * list.size()));
    T *cur_ptr = tmp_ptr;
    try {
        for (T1 el: list) {
            new(cur_ptr) T(el);
            ++cur_ptr;
        }
    } catch (...) {
        for (T *ptr = tmp_ptr; ptr != cur_ptr; ++ptr) {
            ptr->~T();
        }
        delete reinterpret_cast<void *>(tmp_ptr);
        throw;
    }
    m_ptr = tmp_ptr;
    m_rows = list.size();
    m_columns = 1;
    m_capacity = m_rows;
}

template<typename T>
linalg::Matrix<T>::~Matrix() noexcept {
    for (T *ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr) {
        ptr->~T();
    }
    delete reinterpret_cast<void *> (m_ptr);
}

template<typename T>
linalg::Matrix<T> &linalg::Matrix<T>::operator=(const Matrix &matrix) {
    if (&matrix == this) {
        return *this;
    }
    return operator=<T>(matrix);
}

template<typename T>
template<typename T2>
linalg::Matrix<T> &linalg::Matrix<T>::operator=(const Matrix <T2> &matrix) {
    if (matrix.m_rows * matrix.m_columns > m_capacity) {
        return *this = Matrix(matrix);
    }
    size_t i = 0;
    if (m_rows * m_columns < matrix.m_rows * matrix.m_columns) { // Const
        for (; i < m_rows * m_columns; ++i) {
            m_ptr[i] = matrix.m_ptr[i];
        }
        try {
            for (; i < matrix.m_rows * matrix.m_columns; ++i) {
                new(m_ptr + i) T(matrix.m_ptr[i]);
            }
        } catch (...) {
            --i;
            for (; i >= m_rows * m_columns; --i) {
                m_ptr[i].~T();
            }
            throw;
        }
    } else {
        for (; i < matrix.m_rows * matrix.m_columns; ++i) { // Dest
            m_ptr[i] = matrix.m_ptr[i];
        }
        for (; i < m_rows * m_columns; ++i) {
            m_ptr[i].~T();
        }
    }
    m_rows = matrix.m_rows;
    m_columns = matrix.m_columns;
    return *this;
}

template<typename T>
linalg::Matrix<T> &linalg::Matrix<T>::operator=(Matrix &&matrix) noexcept {
    swap(matrix);
    return *this;
}

template<typename T>
void linalg::Matrix<T>::reshape(size_t rows, size_t cols) {
    if (rows * cols != m_rows * m_columns) {
        throw MatrixReshapeError("Incorrect shape");
    }
    m_rows = rows;
    m_columns = cols;
}

template<typename T>
void linalg::Matrix<T>::reserve(size_t n) {
    if (m_rows * m_columns >= n) {
        return;
    }
    T *tmp_ptr = reinterpret_cast<T *> (operator new(sizeof(T) * n));
    T *cur_ptr = tmp_ptr;
    try {
        for (T *ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr, ++cur_ptr) {
            new(cur_ptr) T(*ptr);
        }
    } catch (...) {
        for (T *ptr = tmp_ptr; ptr != cur_ptr; ++ptr) {
            ptr->~T();
        }
        delete reinterpret_cast<void *>(tmp_ptr);
    }
    for (T *ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr) {
        ptr->~T();
    }
    delete reinterpret_cast<void *> (m_ptr);
    m_ptr = tmp_ptr;
    m_capacity = n;
}

template<typename T>
void linalg::Matrix<T>::shrink_to_fit() {
    if (m_capacity == m_rows * m_columns) {
        return;
    }
    *this = Matrix(*this);
}

template<typename T>
void linalg::Matrix<T>::clear() noexcept {
    for (T *ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr) {
        ptr->~T();
    }
    m_rows = m_columns = 0;
}

template<typename T>
void linalg::Matrix<T>::swap(Matrix &matrix) noexcept {
    std::swap(m_ptr, matrix.m_ptr);
    std::swap(m_rows, matrix.m_rows);
    std::swap(m_columns, matrix.m_columns);
    std::swap(m_capacity, matrix.m_capacity);
}

template<typename T>
linalg::Matrix<T> &linalg::Matrix<T>::operator-() {
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = -m_ptr[i];
    }
}

template<typename T>
template<typename Other>
linalg::Matrix<T> &linalg::Matrix<T>::operator+=(const Matrix <Other> &matrix) {
    if (m_rows != matrix.m_rows || m_columns != matrix.m_columns) {
        throw MatrixCalculateError("Can't + these matrix");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] += matrix.m_ptr[i];
    }
    return *this;
}

template<typename T>
template<typename Other>
linalg::Matrix<T> &linalg::Matrix<T>::operator-=(const Matrix <Other> &matrix) {
    if (m_rows != matrix.m_rows || m_columns != matrix.m_columns) {
        throw MatrixCalculateError("Can't - these matrix");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] -= matrix.m_ptr[i];
    }
    return *this;
}

template<typename T>
template<typename Other>
auto linalg::Matrix<T>::operator*=(const Matrix <Other> &matrix) -> Matrix<decltype(T() * Other())> {
    if (m_columns != matrix.m_rows) {
        throw MatrixCalculateError("Can't multiply these matrix. columns of own aren't equal to rows of given");
    }
    Matrix<decltype(T() * Other())> tmp = Matrix(m_rows, matrix.m_columns);
    for (size_t i = 0; i < tmp.m_rows; ++i) {
        for (size_t j = 0; j < tmp.m_columns; ++j) {
            for (size_t k = 0; k < m_columns; ++k) {
                tmp(i, j) += (*this)(i, k) * matrix(k, j);
            }
        }
    }
    return *this = tmp;
}

template<typename T1, typename T2>
auto linalg::operator*(const Matrix <T1> &matrix1, const Matrix <T2> &matrix2) {
    if (matrix1.columns() != matrix2.rows()) {
        throw MatrixCalculateError(
                "Can't multiply these matrix. columns of the first aren't equal to rows of the second");
    }
    Matrix<decltype(T1() * T2())> tmp = Matrix(matrix1.rows(), matrix2.columns());
    for (size_t i = 0; i < tmp.rows(); ++i) {
        for (size_t j = 0; j < tmp.columns(); ++j) {
            for (size_t k = 0; k < matrix1.columns(); ++k) {
                tmp(i, j) += matrix1(i, k) * matrix2(k, j);
            }
        }
    }
    return tmp;
}

template<typename T>
template<typename Tn>
linalg::Matrix<T> &linalg::Matrix<T>::operator*=(const Tn &num) {
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] *= num;
    }
    return *this;
}

template<typename T, typename Tn>
auto linalg::operator*(const Matrix <T> &matrix, const Tn &num) {
    Matrix<decltype(T() * Tn())> res = matrix;
    return res *= num;
}

template<typename T, typename Tn>
auto linalg::operator*(const Tn &num, const Matrix <T> &matrix) {
    Matrix<decltype(T() * Tn())> res = matrix;
    return res *= num;
}

/*template<typename T>
double linalg::Matrix<T>::det() {
    if (m_rows != m_columns) {
        throw MatrixCalculateError("Can't calculate det of this matrix");
    }
    if (m_rows == 1) {
        return m_ptr[0];
    } else {
        double res = 0;
        for (size_t lin = 0; lin < m_rows; ++lin) {
            Matrix <T> tmp = Matrix(m_rows - 1, m_columns - 1);
            for (size_t i = 0, i_tmp = 0; i < m_rows * m_columns; ++i) {
                if (!((i >= lin * m_columns && i < lin * m_columns + m_columns) || i % m_columns == lin)) {
                    tmp.m_ptr[i_tmp] = m_ptr[i];
                    ++i_tmp;
                }
            }
            double det_cur = tmp.det();
            if (lin % 2 == 0) {
                res += det_cur * (*this)(lin, 0);
            } else {
                res -= det_cur * (*this)(lin, 0);
            }
        }
        return res;
    }
}*/
