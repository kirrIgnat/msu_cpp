#ifndef MATRIX_H
#define MATRIX_H 1
#include <vector>
#include <iostream>
#include <stdexcept>
constexpr double MATRIX_EPS = 1e-8;
class Matrix
{
private:
    int m;
    int n;
    std::vector<double> elems;
    std::vector<double> right;

public:
    Matrix(int r = 1, int c = 1) : m(r), n(c), elems(m * n), right(n)
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

    double at(int i, int j) const
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
    
    double ans(int i) const
    {
        return right[i];
    }
    double &ans(int i)
    {
        return right[i];
    }

    const double *operator[](int i) const
    {
        return elems.data() + i * n;
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
    void one(int i, int j);
    void minus(int i,int k, double c);
    void addRows(int i, int k, double c);
    void addRows(int i, int k, double c, double d);
};

std::ostream &operator<<(std::ostream &s, const Matrix &a);

#endif
