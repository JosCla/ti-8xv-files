#ifndef FILEUTILS_H
#define FILEUTILS_H
// fileutils.h
// Various utilities for reading files

// C++ Standard Library
#include <iostream>
#include <string>

int readIntFromHex(std::istream &in, int charLen);
int hexCharsToInt(std::string str);
int hexCharsToInt(char* str, int len);
int checksumVal(int n);
std::string numToHex(int n, unsigned int min_len);

#endif // FILEUTILS_H
