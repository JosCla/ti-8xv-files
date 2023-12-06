// fileutils.cpp
// Implements fileutils.h.

#include <iostream>
using std::istream;
#include <string>
using std::string;

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

int hexCharsToInt(string str) {
    return hexCharsToInt(&(str[0]), str.length());
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

int checksumVal(int n) {
    return (n % 256) + (n / 256);
}

string numToHex(int n, unsigned int min_len) {
    string res = "";
    while (true) {
        res += (char)(n & 255);
        n = n / 256;
        if (n == 0) {break;}
    }

    while (res.size() < min_len) {
        res += '\0';
    }

    return res;
}
