#include <iostream>
#include "utf8.h"
using namespace std;

int main() {
    while (true) {
        int code_point;
        cout << "Code point: ";
        cin >> code_point;
        if (cin.fail() || code_point < 0)
            break;
        output_utf8(cout, code_point);
        cout << endl;
    }
    return 0;
}
