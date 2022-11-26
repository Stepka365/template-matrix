#include "matrix_utilities.h"

std::ostream &linalg::operator<<(std::ostream &out, const linalg::Matrix &matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        out << '|';
        for (size_t j = 0; j < matrix.columns(); ++j) {
            out.width(5);
            out << matrix(i, j);
        }
        out << '|';
        if (i != matrix.rows() - 1){
            out << '\n';
        }
    }
    return out;
}


