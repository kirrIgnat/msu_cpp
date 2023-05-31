#include <iostream>

using namespace std;

int main() {
    while (true) {
        int c = cin.get();
        if (!cin.good())
            break;
        cout << "c = " << c << " \'" << char(c) << "\'" << endl;
    }
    return 0;
}
