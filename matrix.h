#pragma once

#include <cstddef>

namespace linalg {
    class Matrix {
    public:
        Matrix() = default;

        size_t rows() { return m_rows; }

        size_t columns() { return m_columns; }

        size_t capacity() { return m_capacity; }

    private:
        double *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
        size_t m_capacity = 0;
    };
}
