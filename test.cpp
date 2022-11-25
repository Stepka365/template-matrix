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

void test_reserve(){
    using namespace linalg;

    Matrix m(2, 4);
    m.reserve(20);
    m.print();
    std::cout << "m_capacity " << m.capacity() << ' ';
    std::cout << "m_rows " << m.rows() << ' ';
    std::cout << "m_columns " << m.columns() << ' ';
}
void test_shrink(){
    using namespace linalg;

    Matrix m(2, 4);
    m.reserve(20);
    m.print();
    std::cout << "m_capacity " << m.capacity() << ' ';
    std::cout << "m_rows " << m.rows() << ' ';
    std::cout << "m_columns " << m.columns() << ' ';
    std::cout << std::endl;

    m.shrink_to_fit();
    m.print();
    std::cout << "m_capacity " << m.capacity() << ' ';
    std::cout << "m_rows " << m.rows() << ' ';
    std::cout << "m_columns " << m.columns() << ' ';
    std::cout << std::endl;

}

void test_copy(){
    using namespace linalg;

    Matrix m1(2, 3);
    Matrix m2 = m1;
    m2.print();
    std::cout << "m_capacity " << m2.capacity() << ' ';
    std::cout << "m_rows " << m2.rows() << ' ';
    std::cout << "m_columns " << m2.columns() << ' ';
    std::cout << std::endl;

    Matrix m3;
    m3 = m1;
    m3.print();
    std::cout << "m_capacity " << m3.capacity() << ' ';
    std::cout << "m_rows " << m3.rows() << ' ';
    std::cout << "m_columns " << m3.columns() << ' ';
    std::cout << std::endl;
}