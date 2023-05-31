#include "Matrix.h"
using namespace std;
int main()
{
    cout << "enter matrix dimensions(m n):" << endl;
    int m, n;
    m = 3;
    n =3;
    if (!cin.good())
    {
        return (-1);
    }
    Matrix a(m, n);
    cout << "enter matrix:" << endl;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> a.at(i, j);
        }
    }
    
    cout << "enter rigth col:" << endl;
    for (int f = 0; f< n; ++f)
    {
        cin >> a.ans(f);
    }
    cout << "internal matrix" << endl;
    cout << a << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << a.ans(i)<<endl;
    }
    //int rank = a.gaus();
    //cout << a;
    //cout << "rank Matrix:" << endl;
   // cout << rank << endl;
    a.rowEchelonForm();
    cout << "Matrix:" << endl;
    cout << a;
    cout << "Vector:"<< endl;
    for (int i = 0; i < n; ++i)
    {
        cout << a.ans(i)<<endl;
    }
    return 0;
}
