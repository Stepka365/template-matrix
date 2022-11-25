#include "matrix_utilities.h"

#include <iostream>
void linalg::print(Matrix& matrix) {
    for (size_t i = 0; i < matrix.m_rows; ++i) {
        for (size_t j = 0; j < matrix.m_columns; ++j) {
            std::cout << matrix.m_ptr[i * matrix.m_columns + j] << ' ';
        }
        std::cout << '\n';
    }
}