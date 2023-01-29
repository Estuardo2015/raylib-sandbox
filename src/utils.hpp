#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include "string"
#include "chunk.hpp"

char *StrToCharArr(std::string s) {
    const int length = s.length();
    char *char_array = new char[length + 1];
    std::strcpy(char_array, s.c_str());

    return char_array;
}

#endif