#include "ConsoleInputStream.h"
#include <iostream>
#include <string>


int ConsoleInputStream::get() {
    if (!std::cin) return EOF;
    int ch = std::cin.get();
    if (!std::cin) return EOF;
    return ch;
}

bool ConsoleInputStream::eof() {
    return std::cin.eof() || std::cin.fail();
}

