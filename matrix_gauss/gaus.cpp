#include "Matrix.h"
using namespace std;
int main()
{
    cout << "enter matrix dimensions(m n):" << endl;
    int m, n;
    //cin >> m >> n;
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
    cout << "internal matrix" << endl;
    cout << a;
    a.rowEchelonForm();
    cout << "echelonized Matrix:" << endl;
    cout << a;
    //cout << "rank = " << rank << endl;
    return 0;
}