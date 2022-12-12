#pragma once

#include <iomanip>

template<typename T>
void compute_width(const linalg::Matrix<T> &matrix, size_t &first, size_t &other) {
    std::stringstream s_str;
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.columns(); ++j) {
            s_str << matrix(i, j);
            if ((i * matrix.columns() + j) % matrix.columns() == 0) {
                if (s_str.str().size() > first) {
                    first = s_str.str().size();
                }
            } else {
                if (s_str.str().size() > other) {
                    other = s_str.str().size();
                }
            }
            s_str.str("");
        }
    }
}

template<typename T>
std::ostream &linalg::operator<<(std::ostream &out, const linalg::Matrix<T> &matrix) {
    if (matrix.empty()) {
        out << "Your matrix is empty! Nothing to print!";
        return out;
    }
    size_t first_w = 0, other_w = 0;
    compute_width(matrix, first_w, other_w);
    for (size_t i = 0; i < matrix.rows(); ++i) {
        out << '|';
        for (size_t j = 0; j < matrix.columns(); ++j) {
            if ((i * matrix.columns() + j) % matrix.columns() == 0) {
                out << std::setw(first_w);
            } else {
                out << std::setw(other_w + 1);
            }
            out << matrix(i, j);
        }
        out << '|';
        if (i != matrix.rows() - 1) {
            out << '\n';
        }
    }
    return out;
}