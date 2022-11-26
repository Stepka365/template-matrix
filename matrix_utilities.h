#pragma once

#include "matrix.h"
#include <ostream>

namespace linalg {
    std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
}
