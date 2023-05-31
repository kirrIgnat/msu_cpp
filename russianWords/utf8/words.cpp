#include <iostream>
#include <vector>
#include <map>
// #include <pair>
#include <algorithm>
#include "utf8.h"

using namespace std;
typedef vector<int> Word;

int main() {
    map<Word, int> dictionary;
    int state = 0; // 0 out of word, 1 inside a word
    Word currentWord;
    bool fails = false;
    while (!fails) {
        int codePoint = get_utf8_code_point(cin, fails);
        //... cout << "Code point = " << codePoint << endl;
        if (state == 0) {
            if (isRussianLetter(codePoint)) {
                //... cout << "Russian letter" << endl;
                currentWord.clear();
                currentWord.push_back(codePoint);
                state = 1;
            }
        } else if (state == 1) {
            // Inside a word
            if (isRussianLetter(codePoint)) {
                currentWord.push_back(codePoint);
            } else {
                // End of word
                if (dictionary.find(currentWord) ==
                    dictionary.end()) {
                    // This is a new word,
                    // add it to the dictionary
                    dictionary[currentWord] = 1;
                } else {
                    // The word is already in the dictionary
                    ++(dictionary[currentWord]);
                }
                state = 0; // Go out of word
            }
        }
    } // end of while

    vector< pair<int, Word> > pairs;
    map<Word, int>::const_iterator i = dictionary.begin();
    while (i != dictionary.end()) {
        pairs.push_back(
            pair<int, Word>(i->second, i->first)
        );
        ++i;
    }

    stable_sort(pairs.begin(), pairs.end());

    // Print results
    for (int i = 0; i < pairs.size(); ++i) {
        // Print a word
        for (int j = 0; j < pairs[i].second.size(); ++j) {
            output_utf8(cout, pairs[i].second[j]);
        }
        // Print its frequence
        cout << ' ' << pairs[i].first << endl;
    }

    return 0;
}
