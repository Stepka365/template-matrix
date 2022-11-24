#include "test.h"
#include "matrix.h"

#include <iostream>

void linalg::Matrix::print() {
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            std::cout << m_ptr[i * m_columns + j] << ' ';
        }
        std::cout << '\n';
    }
}

void test_base_init(){
    using namespace linalg;

    Matrix m(2, 4);
    m.reshape(4, 2);
    m.print();
    std::cout << m.empty() << '\n';
    Matrix m2;
    std::cout << m2.empty() << '\n';

}