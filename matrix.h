#pragma once

#include <cstddef>

namespace linalg {
    class Matrix {
    public:
        Matrix() = default;

        Matrix(size_t rows, size_t cols = 1);

        Matrix(const Matrix &matrix);

        ~Matrix() { delete[]m_ptr; }

        Matrix &operator=(const Matrix &matrix);

        size_t rows() const { return m_rows; }

        size_t columns() const { return m_columns; }

        size_t capacity() const { return m_capacity; }

        bool empty() const { return m_ptr == nullptr; }

        void reshape(size_t rows, size_t cols);

        void reserve(size_t n);

        void shrink_to_fit();

        void clear() { m_columns = m_rows = 0; }

        void print();

    private:
        double *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
        size_t m_capacity = 0;
    };
}
