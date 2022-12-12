#include "test.h"
#include "matrix_utilities.h"

#include <iostream>

void run_all_tests() {
    test_init_reshape_empty();
    test_reserve();
    test_shrink();
    test_copy();
    test_const();
    test_clear();
    test_move();
    test_init_list();
    test_brackets();
    test_print();
    test_template();
}

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

    Matrix m = {{1, 2, 3, 4},
                {5, 6, 7, 8}};
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
        if (m2.capacity() == 6 && m2.rows() == 2 && m2.columns() == 3) {
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
    if (m1.empty() && m2.empty()) {
        std::cout << __FUNCTION__ << " Passed\n";
        return;
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_move() {
    using namespace linalg;

    Matrix m1(2, 4), m3;
    m1.reserve(15);
    Matrix m2 = Matrix(3, 5);
    m3 = std::move(m1);
    if (m1.empty()) {
        if (m3.rows() == 2 && m3.columns() == 4 && m3.capacity() == 15) {
            if (m2.rows() == 3 && m2.columns() == 5 && m2.capacity() == 15) {
                std::cout << __FUNCTION__ << " Passed\n";
                return;
            }
        }
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_init_list() {
    using namespace linalg;

    Matrix m1 = {1, 2, 3, 4, 5};
    if (m1.rows() == 5 && m1.columns() == 1 && m1.capacity() == 5) {
        Matrix m2 = {{1, 2, 3},
                     {4, 5, 6}};
        if (m2.rows() == 2 && m2.columns() == 3 && m2.capacity() == 6) {
            std::cout << __FUNCTION__ << " Passed\n";
            return;
        }
    }
    std::cout << __FUNCTION__ << "  FAILED\n";
}

void test_brackets() {
    using namespace linalg;

    Matrix m = {{1.0, 4.0, 9.0},
                {3.0, 6.0, 9.0}};

    double x = m(0, 1);
    if (x == 4) {
        x = 24;
        if (m(0, 1) == 4) {
            double &elem = m(0, 1);
            elem = 24;
            if (m(0, 1) == 24) {
                const Matrix m2 = std::move(m);
                double y = m2(1, 0);
                if (y == 3) {
                    y = 50;
                    if (m2(1, 0) == 3) {
                        std::cout << __FUNCTION__ << " Passed\n";
                        return;
                    }
                }
            }
        }
    }
    std::cout << __FUNCTION__ << " FAILED\n";
}

void test_print() {
    using namespace linalg;

    Matrix m = {{1,   40, 9999},
                {113, 6,  9}};

}

void test_template() {
    using namespace linalg;

    Matrix<double> m(2,4);
    m(0,0) = 10.5;
    std::cout << m;
}