#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace linalg {
    template<typename T = double>
    class Matrix {
    public:
        template<typename Other> friend
        class Matrix;

        Matrix() = default;

        Matrix(size_t rows, size_t cols = 1);

        Matrix(const Matrix &matrix);

        template<typename T2>
        Matrix(const Matrix<T2> &matrix);

        Matrix(Matrix &&matrix) noexcept { swap(matrix); }

        template<typename T1>
        Matrix(std::initializer_list<std::initializer_list<T1>>);

        template<typename T1>
        Matrix(std::initializer_list<T1>);

        ~Matrix() noexcept;

        Matrix &operator=(const Matrix &matrix);

        template<typename T2>
        Matrix &operator=(const Matrix<T2> &matrix);

        Matrix &operator=(Matrix &&matrix) noexcept;

        T &operator()(size_t row, size_t col) noexcept { return m_ptr[row * m_columns + col]; }

        const T &operator()(size_t row, size_t col) const noexcept { return m_ptr[row * m_columns + col]; };

        size_t rows() const noexcept { return m_rows; }

        size_t columns() const noexcept { return m_columns; }

        size_t capacity() const noexcept { return m_capacity; }

        bool empty() const noexcept { return m_rows == 0 && m_columns == 0; }

        void reshape(size_t rows, size_t cols);

        void reserve(size_t n);

        void shrink_to_fit();

        void clear() noexcept;

        void swap(Matrix &matrix) noexcept;

        Matrix &operator-();

        Matrix &operator+=(const Matrix &matrix);

        Matrix &operator-=(const Matrix &matrix);

        Matrix &operator*=(const Matrix &matrix);

        template<typename Tn>
        Matrix &operator*=(const Tn &num);

    private:
        template<typename T2>
        void copy_constructor(const Matrix<T2> &matrix);

    private:
        T *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
        size_t m_capacity = 0;
    };

    template<typename T>
    inline void swap(Matrix<T> &matrix1, Matrix<T> &matrix2) noexcept { matrix1.swap(matrix2); }

    template<typename T>
    auto operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
        Matrix<T> result = matrix1;
        return result += matrix2;
    }

    template<typename T>
    auto operator-(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
        Matrix<T> result = matrix1;
        return result -= matrix2;
    }


    class MatrixException : public std::runtime_error {
    public:
        MatrixException(const char *message) : std::runtime_error(message) {}
    };

    class MatrixInitError : public MatrixException {
    public:
        MatrixInitError(const char *message) : MatrixException(message) {}
    };

    class MatrixReshapeError : public MatrixException {
    public:
        MatrixReshapeError(const char *message) : MatrixException(message) {}
    };

    class MatrixCalculateError : public MatrixException {
    public:
        MatrixCalculateError(const char *message) : MatrixException(message) {}
    };

    template<typename T>
    auto operator*(const Matrix<T> &matrix1, const Matrix<T> &matrix2);

    template<typename T, typename Tn>
    auto operator*(const Matrix<T> &matrix, const Tn &num);

    template<typename T, typename Tn>
    auto operator*(const Tn &num, const Matrix<T> &matrix);
}

#include "matrix.hpp"