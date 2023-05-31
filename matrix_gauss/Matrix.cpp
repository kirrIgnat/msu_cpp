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
        for (int k = i + 1; k < m; ++k)
        {
            addRows(k, i, -at(k, j) / at(i, j));
        }
        ++i;
        ++j;
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

std::ostream &operator<<(std::ostream &s, const Matrix &a)
{
    std::stringstream txt;
    txt << std::fixed << std::setprecision(4);
    int maxWidth = 0;
    for (int i = 0; i < a.rows(); ++i)
    {
        for (int j = 0; j < a.cols(); ++j)
        {
            // txt.clear();
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
            // txt.clear();
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