#pragma once

#include "matrix.h"
#include <ostream>

namespace linalg {
    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix);
}

#include "matrix_utilities.hpp"