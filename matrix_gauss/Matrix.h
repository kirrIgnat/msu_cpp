#ifndef MATRIX_H
#define MATRIX_H 1
#include <vector>
#include <iostream>
#include <stdexcept>
constexpr double MATRIX_EPS = 1e-8; // точность

class Matrix
{
private:
    int m;                     // rows
    int n;                     // colomns
    std::vector<double> elems; //?

public:
    Matrix(int r = 1, int c = 1) : m(r), n(c), elems(m * n)
    {
    }

    int rows() const
    {
        return m;
    }

    int colomns() const
    {
        return n;
    }

    int cols() const
    {
        return colomns();
    }

    void resize(int r, int c)
    {
        m = r;
        n = c;
        elems.resize(m * n);
    }

    double at(int i, int j) const // возвращает ссылку на константный элемент например a11 (читает элемент)
    {
        if (i < 0 || j >= m || i < 0 || j >= n)
        {
            throw std::range_error("Matrix out of range");
        }
        return elems[i * n + j];
    }

    double &at(int i, int j)
    {
        if (i < 0 || j >= m || i < 0 || j >= n)
        {
            throw std::range_error("Matrix out of range");
        }
        return elems[i * n + j];
    }

    const double *operator[](int i) const
    {
        return elems.data() + i * n; // указатель на 1й элемент массива
    }

    double *operator[](int i)
    {
        return elems.data() + i * n;
    }

    int gaus(); // return rank
    void rowEchelonForm();
    double det() const;
    Matrix inverse() const;

    void swapRows(int i, int k);
    void addRows(int i, int k, double c);
};

std::ostream &operator<<(std::ostream &s, const Matrix &a);

#endif