// fileutils.cpp
// Implements fileutils.h.

#include <iostream>
using std::istream;

#include "fileutils.h"

int readIntFromHex(istream &in, int charLen) {
    char str[charLen];
    for (int i = 0; i < charLen; i++) {
        char c;
        in.get(c);
        str[i] = c;
    }

    return hexCharsToInt(str, charLen);
}

int hexCharsToInt(char* str, int len) {
    int total = 0;
    for (int i = len - 1; i >= 0; i--) {
        total *= 256;

        int val = str[i];
        if (val < 0) {val += 256;}

        total += val;
    }

    return total;
}
