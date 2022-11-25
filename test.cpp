#include "test.h"
#include "matrix_utilities.h"

#include <iostream>

void test_base_init(){
    using namespace linalg;

    Matrix m(2, 4);
    m.reshape(4, 2);
    print(m);
    std::cout << m.empty() << '\n';
    Matrix m2;
    std::cout << m2.empty() << '\n';

}

void test_reserve(){
    using namespace linalg;

    Matrix m(2, 4);
    m.reserve(20);
    print(m);
    std::cout << "m_capacity " << m.capacity() << ' ';
    std::cout << "m_rows " << m.rows() << ' ';
    std::cout << "m_columns " << m.columns() << ' ';
}
void test_shrink(){
    using namespace linalg;

    Matrix m(2, 4);
    m.reserve(20);
    print(m);
    std::cout << "m_capacity " << m.capacity() << ' ';
    std::cout << "m_rows " << m.rows() << ' ';
    std::cout << "m_columns " << m.columns() << ' ';
    std::cout << std::endl;

    m.shrink_to_fit();
    print(m);
    std::cout << "m_capacity " << m.capacity() << ' ';
    std::cout << "m_rows " << m.rows() << ' ';
    std::cout << "m_columns " << m.columns() << ' ';
    std::cout << std::endl;

}

void test_copy(){
    using namespace linalg;

    Matrix m1(2, 3);
    Matrix m2 = m1;
    print(m2);
    std::cout << "m_capacity " << m2.capacity() << ' ';
    std::cout << "m_rows " << m2.rows() << ' ';
    std::cout << "m_columns " << m2.columns() << ' ';
    std::cout << std::endl;

    Matrix m3;
    m3 = m1;
    print(m3);
    std::cout << "m_capacity " << m3.capacity() << ' ';
    std::cout << "m_rows " << m3.rows() << ' ';
    std::cout << "m_columns " << m3.columns() << ' ';
    std::cout << std::endl;
}

void test_const(){
    using namespace linalg;

    const Matrix m(2, 5);

}

void test_clear(){
    using namespace linalg;

    Matrix m1(2, 4), m2;
    std::cout << std::boolalpha;
    std::cout << m1.empty() << '\n';
    std::cout << m2.empty() << '\n';
}