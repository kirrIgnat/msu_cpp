#ifndef UTF8_H
#define UTF8_H

#include <iostream>

int get_utf8_code_point(std::istream& stream, bool& readFails);
bool output_utf8(std::ostream& stream, int code_point);
bool isRussianLetter(int code_point);

#endif
