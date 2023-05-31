#include <iostream>
#include "utf8.h"
using namespace std;

int main() {
    bool readFails = false;
    int n = 0;
    while (!readFails) {
        int code_point = get_utf8_code_point(cin, readFails);
        if (code_point >= 0) {
            if (n > 0) {
                if (n % 10 == 0)
                    cout << endl;
                else
                    cout << ' ';
            }
            cout << code_point;
            if (code_point == '\n')
                cout << endl;
            ++n;
        }
    }
    return 0;
}
