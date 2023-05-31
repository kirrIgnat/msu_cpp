#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "utf8.h"

using namespace std;

static int findCodePoint(int code_point);
static void initializeConvertion();
static void printHelp();

// CP1251 Code page
const int CP1251_UNICODE[256] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 
    0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 
    0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 
    0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 
    0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 
    0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 
    0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 
    0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 
    0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
    0x0402, 0x0403, 0x201A, 0x0453, 0x201E, 0x2026, 0x2020, 0x2021, 
    0x20AC, 0x2030, 0x0409, 0x2039, 0x040A, 0x040C, 0x040B, 0x040F,
    0x0452, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 
    0x0098, 0x2122, 0x0459, 0x203A, 0x045A, 0x045C, 0x045B, 0x045F,
    0x00A0, 0x040E, 0x045E, 0x0408, 0x00A4, 0x0490, 0x00A6, 0x00A7, 
    0x0401, 0x00A9, 0x0404, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0407,
    0x00B0, 0x00B1, 0x0406, 0x0456, 0x0491, 0x00B5, 0x00B6, 0x00B7, 
    0x0451, 0x2116, 0x0454, 0x00BB, 0x0458, 0x0405, 0x0455, 0x0457,
    0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
    0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F,
    0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 
    0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F,
    0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 
    0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F,
    0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 
    0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F
};

// CodeDescriptor is a pair < UNICODE code point, CP1251 code >
class CodeDescriptor: public pair<int, int> {
public:
    CodeDescriptor():
        pair<int, int>()
    {}

    CodeDescriptor(int code_point, int rusCode):
        pair<int, int>(code_point, rusCode)
    {}

    bool operator==(const CodeDescriptor& cd) const {
        return (first == cd.first);
    }
    bool operator<=(const CodeDescriptor& cd) const {
        return (first <= cd.first);
    }
    bool operator<(const CodeDescriptor& cd) const {
        return (first < cd.first);
    }
    bool operator>=(const CodeDescriptor& cd) const {
        return (first >= cd.first);
    }
    bool operator>(const CodeDescriptor& cd) const {
        return (first > cd.first);
    }
};

// The following table contains pairs (first = Unicode point, second = CP1251 code)
// The first components will be sorted in ascending order
vector<CodeDescriptor> convertion_table;

int main(int argc, char *argv[]) {
    if (argc > 1 && argv[1][0] == '-') {
        printHelp();
        return 0;
    }
    istream *in = &cin;
    ostream *out = &cout;
    bool readFromFile = false;
    bool writeToFile = false;
    ifstream file_in; 
    ofstream file_out;
    if (argc > 1) {
        file_in.open(argv[1], fstream::in | fstream::binary);
        if (!file_in.is_open()) {
            cerr << "Could not open the input file" << endl;
            return (-1);
        }
        in = &file_in;
        readFromFile = true;
    }
    if (argc > 2) {
        file_out.open(argv[2], fstream::out | fstream::binary);
        if (!file_out.is_open()) {
            cerr << "Could not open the output file" << endl;
            return (-1);
        }
        out = &file_out;
        writeToFile = true;
    }

    initializeConvertion();

    int res = 0;
    bool notUtf8 = false;

    // Check BOM
    int c0 = in->peek();
    if (c0 != EOF) {
        // The UTF-8 representation of the BOM is the (hexadecimal) 
        // byte sequence 0xEF,0xBB,0xBF.
        c0 &= 0xFF;
        if (c0 == 0xEF) {
            // Skip BOM
            in->get();
            in->get();
            in->get();
        }
    }

    while (true) {
        bool readFails;
        int code_point = get_utf8_code_point(*in, readFails);
        if (readFails)
            break;      // End of file
        if (code_point < 0) {
            // Incorrect format of file
            notUtf8 = true;
            (*out) << '?';
        } else {
            int idx = findCodePoint(code_point);
            if (idx < 0) {
                // The character is not in the CP1251 table
                (*out) << '?';
            } else {
                assert(idx < 256);
                unsigned char c = 
                    (unsigned char)(convertion_table.at(idx).second);
                out->put(c);
                if (out->fail()) {
                    cerr << "Write error." << endl;
                    res = (-1);
                    break;
                }
            }
        }
    }
    if (readFromFile) {
        file_in.close();
    }
    if (writeToFile) {
        file_out.close();
    }
    if (notUtf8) {
        cerr << "The file encoding probably is not UTF8." << endl;
    }
    return res;
}

static void initializeConvertion() {
    convertion_table.resize(256);
    for (int i = 0; i < 256; ++i) {
        convertion_table[i].second = i;
        convertion_table[i].first = CP1251_UNICODE[i];
    }
    sort(convertion_table.begin(), convertion_table.end());
}

static int findCodePoint(int code_point) {
    CodeDescriptor cd(code_point, 0);
    vector<CodeDescriptor>::const_iterator i =
        lower_bound(convertion_table.begin(), convertion_table.end(), cd);
    if (i == convertion_table.end())
        return (-1);
    return int(i - convertion_table.begin());
}

static void printHelp() {
    cout << "Convert a text file from UTF8 encoding to Windows CP1251 Russian." << endl;
    cout << "Usage:" << endl;
    cout << "    utf2win [fileIn [fileOut]]" << endl;
    cout << "If fileIn is not given, then the program reads text from" << endl;
    cout << "the  standard input and writes to the standard output." << endl;
    cout << "If only fileOut is not given, then the program reads" << endl;
    cout << "the input file and writes to the standard output." << endl;
}
