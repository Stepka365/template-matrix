#include "test.h"
#include "matrix_utilities.h"

#include <iostream>

void test_init_reshape_empty() {
    using namespace linalg;

    Matrix m(2, 4);
    if (m.rows() == 2 && m.columns() == 4 && m.capacity() == 8) {
        try {
            m.reshape(3, 2);
        } catch (std::runtime_error &e) {
            m.reshape(2, 4);
            if (!m.empty()) {
                Matrix m2;
                if (m2.empty()) {
                    std::cout << __FUNCTION__ << " Passed\n";
                    return;
                }
            }
        }
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_reserve() {
    using namespace linalg;

    Matrix m(2, 4);
    m.reserve(3);
    if (m.capacity() == 8 && m.rows() == 2 && m.columns() == 4) {
        m.reserve(20);
        if (m.capacity() == 20 && m.rows() == 2 && m.columns() == 4) {
            std::cout << __FUNCTION__ << " Passed\n";
            return;
        }
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_shrink() {
    using namespace linalg;

    Matrix m(2, 4);
    m.reserve(20);
    m.shrink_to_fit();
    if (m.capacity() == 8 && m.rows() == 2 && m.columns() == 4) {
        std::cout << __FUNCTION__ << " Passed\n";
        return;
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_copy() {
    using namespace linalg;

    Matrix m1(2, 3);
    m1.reserve(10);
    Matrix m2 = m1;
    if (m2.capacity() == 6 && m2.rows() == 2 && m2.columns() == 3) {
        Matrix m3;
        m1.reserve(20);
        m3 = m1;
        if (m2.capacity() == 6 && m2.rows() == 2 && m2.columns() == 3){
            std::cout << __FUNCTION__ << " Passed\n";
            return;
        }
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_const() {
    using namespace linalg;

    const Matrix m(2, 5);
    m.capacity();
    m.columns();
    m.rows();
    m.empty();
    std::cout << __FUNCTION__ << " Passed\n";
}

void test_clear() {
    using namespace linalg;

    Matrix m1(2, 4), m2;
    m1.clear();
    if (m1.empty() && m2.empty()){
        std::cout << __FUNCTION__ << " Passed\n";
        return;
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}