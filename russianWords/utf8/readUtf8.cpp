#include <iostream>
#include "utf8.h"

using namespace std;

int main() {
    while (true) {
        bool fails;
        int codePoint = get_utf8_code_point(cin, fails);
        if (!cin.good())
            break;
        output_utf8(cout, codePoint);
        cout << ": codePoint = " << codePoint << endl;
    }
    return 0;
} 
