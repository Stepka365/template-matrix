#include "test.h"
#include "matrix.h"

#include <iostream>

void test_getter(){
    using namespace linalg;

    Matrix a;
    std::cout << a.columns() << '\n';
}