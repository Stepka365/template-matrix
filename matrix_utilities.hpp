#pragma once

#include <iomanip>
#include <iostream>

template<typename T>
static void compute_width(const linalg::Matrix<T>& matrix, size_t& first, size_t& other) {
    std::stringstream s_str;
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.columns(); ++j) {
            s_str << matrix(i, j);
            if ((i * matrix.columns() + j) % matrix.columns() == 0) {
                if (s_str.str().size() > first) {
                    first = s_str.str().size();
                }
            }
            else {
                if (s_str.str().size() > other) {
                    other = s_str.str().size();
                }
            }
            s_str.str("");
        }
    }
}

template<typename T>
std::ostream& linalg::operator<<(std::ostream& out, const linalg::Matrix<T>& matrix) {
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
            }
            else {
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

template<typename T>
linalg::Matrix<T> minor_forming(const linalg::Matrix<T>& matrix, size_t row, size_t col) {
    linalg::Matrix<T> minor = linalg::Matrix(matrix.rows() - 1, matrix.columns() - 1);
    for (size_t i = 0, i_min = 0; i < matrix.rows(); ++i) {
        if (i == row) {
            continue;
        }
        for (size_t j = 0, j_min = 0; j < matrix.columns(); ++j) {
            if (j == col) {
                continue;
            }
            minor(i_min, j_min) = matrix(i, j);
            ++j_min;
        }
        ++i_min;
    }
    return minor;
}

template<typename T>
auto linalg::det(const Matrix <T>& matrix) -> decltype(T() * T() + T() * T()) {
    if (matrix.rows() != matrix.columns()) {
        throw MatrixCalculateError("Can't calculate det of this matrix");
    }
    if (matrix.rows() == 1) {
        return matrix(0, 0);
    }
    else {
        decltype(T() * T() + T() * T()) res = T();
        for (size_t lin = 0; lin < matrix.rows(); ++lin) {
            linalg::Matrix<T> minor = minor_forming(matrix, lin, 0);
            double det_cur = det(minor);
            if (lin % 2 == 0) {
                res += det_cur * matrix(lin, 0);
            }
            else {
                res -= det_cur * matrix(lin, 0);
            }
        }
        return res;
    }
}