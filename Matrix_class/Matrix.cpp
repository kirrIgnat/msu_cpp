#include "Matrix.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cassert>

int Matrix::gaus()
{
    int i = 0;
    int j = 0;
    while (i < m && j < n)
    {
        double maxVal = fabs(at(i, j));
        double maxIdx = i;
        for (int k = j + 1; k < m; ++k)
        {
            if (fabs(at(k, j)) > maxVal)
            {
                maxVal = fabs(at(k, j));
                maxIdx = k;
            }
        }
        if (maxVal <= MATRIX_EPS)
        {
            ++j;
            continue;
        }
        assert(fabs(at(maxIdx, j)) > MATRIX_EPS);
        
        if (i != maxIdx)
        {
            swapRows(i, maxIdx);
        }
        for (int k = i + 1; k < m; ++k)
        {
            addRows(k, i, -at(k, j) / at(i, j));
        }
        ++i;
        ++j;
    }
    return i;
}

void Matrix::rowEchelonForm()
{
    int i = 0;
    int j = 0;
    while (i < m && j < n)
    {
        double maxVal = fabs(at(i, j));
        double maxIdx = i;
        for (int k = j + 1; k < m; ++k)
        {
            if (fabs(at(k, j)) > maxVal)
            {
                maxVal = fabs(at(k, j));
                maxIdx = k;
            }
        }
        if (maxVal <= MATRIX_EPS)
        {
            ++j;
            continue;
        }
        assert(fabs(at(maxIdx, j)) > MATRIX_EPS);
        if (i != maxIdx)
        {
            swapRows(i, maxIdx);
        }
        
        //std::cout << at(i, j) << std::endl;

     
        for (int k = i + 1; k < m; ++k)
        {
            double c = -at(k, j) / at(i, j);
            addRows(k, i, c, -at(k, j)/at(i,j));
            ans(i) += ans(i) * c;
        }
        one(i, j);
 

        ++i;
        ++j;
    }
}

void Matrix::one(int i, int j){
    double tmp = at(i,j);
    //std::cout << old << std::endl;
    for (int g=0;g<n;++g){

        at(i,g) /= tmp;
        //ans(g) /= tmp;
    }
}

void Matrix::minus(int i, int j, double c)
{
    for (int k=i+1;k<n;++k){
        std::cout << at(k, j) << std::endl;
        at(i,k) -= c;
    }
}

void Matrix::swapRows(int i, int k)
{
    for (int j = 0; j < n; ++j)
    {
        double tmp = at(i, j);
        at(i, j) = at(k, j);
        at(k, j) = (-tmp);
    }
}

void Matrix::addRows(int i, int k, double c)
{
    for (int j = 0; j < n; ++j)
    {
        at(i, j) += at(k, j) * c;
    }
}

void Matrix::addRows(int i, int k, double c, double d)
{
    for (int j = 0; j < n; ++j)
    {
        at(i, j) += at(k, j) * c;

    }
}

std::ostream &operator<<(std::ostream &s, const Matrix &a)
{
    std::stringstream txt;
    txt << std::fixed << std::setprecision(4);
    int maxWidth = 0;
    for (int i = 0; i < a.rows(); ++i)
    {
        for (int j = 0; j < a.cols(); ++j)
        {
            txt.str("");
            txt << a.at(i, j);
            int l = int(txt.str().size());
            if (l > maxWidth)
            {
                maxWidth = l;
            }
        }
    }
    for (int i = 0; i < a.rows(); ++i)
    {
        for (int j = 0; j < a.cols(); ++j)
        {
            if (j > 0)
            {
                s << " ";
            }
            txt.str("");
            txt << a.at(i, j);
            int l = int(txt.str().size());
            for (int k = 0; k < maxWidth - l; ++k)
            {
                s << " ";
            }
            s << txt.str();
        }
        s << std::endl;
    }
    return s;
}
