#include "ConsoleOutputStream.h"
#include <iostream>

void ConsoleOutputStream::put(char c) {
    std::cout.put(c);
}