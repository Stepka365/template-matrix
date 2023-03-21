#pragma once

#include "matrix.h"
#include <ostream>

namespace linalg {
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

    template<typename T>
    auto det(const Matrix<T>& matrix) -> decltype(T() * T() + T() * T());
}

#include "matrix_utilities.hpp"