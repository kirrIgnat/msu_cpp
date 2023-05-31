#include <iostream>
#include <cassert>
#include "utf8.h"

using namespace std;

int get_utf8_code_point(istream& stream, bool& readFails) {
    unsigned char leadingByte, continuationByte;
    int result = 0;
    // stream >> leadingByte;
    leadingByte = stream.get();
    // cout << "Leading byte = " << (unsigned int) leadingByte << endl;

    if (stream.fail()) {
        readFails = true;
        return (-1);
    }
    readFails = false;
    if ((0x80 & leadingByte) == 0) {
        // ASCII character
        return leadingByte;
    }

    // Count the number of continuation bytes
    int k = 0;
    unsigned char bit = 0x80;
    unsigned char mask = 0x7F;  // Mask of data bits in leading byte
    while (k < 6 && (leadingByte & bit) != 0) {
        ++k; bit >>= 1; mask >>= 1;
    }
    if (k == 6 && (leadingByte & bit) != 0) {
        // Illegal character (maybe, BOM)
        return (-1);
    }
    result |= (leadingByte & mask); // Data bits in leading byte
    --k;        // k is the number of continuation bytes

    while (k > 0) {
        // stream >> continuationByte;
        continuationByte = stream.get();

        if (stream.fail()) {
            readFails = true;
            return (-1);
        }
        if ((continuationByte & 0xC0) != 0x80) {
            return (-1);
        }
        result <<= 6;
        result |= (0x3F & continuationByte);
        --k;
    }
    return result;
}

bool output_utf8(std::ostream& stream, int code_point) {
    if ((code_point & 0x80000000) != 0)
        return false;

    // Count a number of bits (from non-zero leading bit)
    int bit = 0x40000000;
    int bitNumber = 30;
    while (bitNumber >= 0 && (bit & code_point) == 0) {
        bit >>= 1; --bitNumber;
    }

    // Theoretical maximal is 6-byte sequence:
    // 1 bit in leading byte,
    // 5*6 bits in continuation bytes
    // But now maximal is 21 bits (4-byte sequence)

    int numBits = bitNumber + 1;
    //... cout << std::dec << "numBits = " << numBits << endl;

    assert(0 <= numBits && numBits <= 31);
    if (numBits > 21)
        return false;

    if (numBits <= 7) {
        // ASCII
        stream << ((char) code_point);
        return stream.good();
    }

    // 1 continuation byte: 5 + 6 = 11 bits
    // 2 continuation bytes: 4 + 6 + 6 = 16 bits
    // 3 continuation bytes: 3 + 6 + 6 + 6 = 21 bits
    int numContBytes = 1;
    if (numBits > 11)
        ++numContBytes;
    if (numBits > 16)
        ++numContBytes;
    //... cout << "numContBytes = " << numContBytes << endl;

    char leadingByte;
    if (numBits > 16) {
        // 4-byte sequence
        assert(numContBytes == 3);
        int mask = 0x07;    // 3 bits in leading byte
        leadingByte = (char)(
            (code_point >> (6*3)) & mask
        );
        leadingByte |= 0xF0;
    } else if (numBits > 11) {
        // 3-byte sequence
        assert(numContBytes == 2);
        int mask = 0x0F;    // 4 bits in leading byte
        leadingByte = (char)(
            (code_point >> (6*2)) & mask
        );
        leadingByte |= 0xE0;
    } else {
        // 2-byte sequence
        assert(numContBytes == 1);
        int mask = 0x1F;    // 5 bits in leading byte
        leadingByte = (char)(
            (code_point >> (6*1)) & mask
        );
        leadingByte |= 0xC0;
    }

    // Write the leading byte
    //... cout << "leadingByte = " << std::hex <<
    //...     ((unsigned int) leadingByte & 0xFF) << endl;
    stream << leadingByte;
    if (stream.fail())
        return false;

    // Write continuation bytes
    for (int i = 1; i <= numContBytes; ++i) {
        char contByte = 0x80;
        contByte |= (char)(
            (code_point >> (6*(numContBytes - i))) & 0x3F
        );
        stream << contByte;
        if (stream.fail())
            return false;
    }
    return true;
}
