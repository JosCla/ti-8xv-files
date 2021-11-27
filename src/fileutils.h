#ifndef FILEUTILS_H
#define FILEUTILS_H
// fileutils.h
// Various utilities for reading files

// C++ Standard Library
#include <iostream>

int readIntFromHex(std::istream &in, int charLen);
int hexCharsToInt(char* str, int len);

#endif // FILEUTILS_H
