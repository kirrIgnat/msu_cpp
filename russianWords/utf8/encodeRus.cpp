#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "utf8.h"

using namespace std;

map<int, int> alphaMap;

vector<int> russianLetters;

int main() {
    russianLetters.resize(33);
    for (int i = 0; i < 32; ++i) {
        russianLetters[i] = i + 1040;
    }
    russianLetters[32] = 1025;  // Yo
    for (int i = 0; i <= 32; ++i) {
        int codePoint = russianLetters[i];
        alphaMap[codePoint] = codePoint;
    }

    // Shuffle
    time_t t;
    srand(time(&t));
    for (int i = 0; i < 1000; ++i) {
        int i0 = russianLetters[rand() % 33];
        int i1 = russianLetters[rand() % 33];
        if (i0 != i1) {
            // Swap 2 letters
            int c0 =  alphaMap[i0];
            int c1 =  alphaMap[i1];
            //... cout << "Swapping " << c0 << ' ' << c1 << endl;
            alphaMap[i0] = c1;
            alphaMap[i1] = c0;
        }
    }

    // Print the encoding
    /*...
    for (int i = 0; i < 33; ++i) {
        int r = russianLetters[i];
        cout << r << " --> " << alphaMap[r] << endl;
    }
    ...*/

    bool fails = false;
    while (!fails) {
        int codePoint = get_utf8_code_point(cin, fails);
        if (fails)
            break;
        if (isRussianLetter(codePoint)) {
            //... cout << codePoint << " -> ";
            codePoint = toUpperLetter(codePoint);
            codePoint = alphaMap[codePoint];
            //... cout << codePoint << endl;
        }
        output_utf8(cout, codePoint);
    }

    return 0;
}
