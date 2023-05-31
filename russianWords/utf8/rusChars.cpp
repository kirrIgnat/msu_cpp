#include <iostream>
#include <vector>
#include <map>
// #include <pair>
#include <algorithm>
#include "utf8.h"

using namespace std;

int main() {
    int totalChars = 0;
    map<int, int> alphabet;
    bool fails = false;
    while (!fails) {
        int codePoint = get_utf8_code_point(cin, fails);
        if (isRussianLetter(codePoint)) {
            ++totalChars;
            codePoint = toUpperLetter(codePoint);
            if (alphabet.find(codePoint) == alphabet.end()) {
                // This is a new letter,
                // add it to the alphabet
                alphabet[codePoint] = 1;
            } else {
                // The letter is already in the alphabet
                ++(alphabet[codePoint]);
            }
        }
    } // end of while

    vector< pair<int, int> > pairs;
    map<int, int>::const_iterator i = alphabet.begin();
    while (i != alphabet.end()) {
        pairs.push_back(
            pair<int, int>(i->second, i->first)
        );
        ++i;
    }

    stable_sort(pairs.begin(), pairs.end());

    // Print results
    for (int i = 0; i < pairs.size(); ++i) {
        // Print a letter
        output_utf8(cout, pairs[i].second);
        // Print its frequence
        cout << ' ' << pairs[i].first << 
            ' ' << (double) pairs[i].first/(double) totalChars << endl;
    }

    return 0;
}
