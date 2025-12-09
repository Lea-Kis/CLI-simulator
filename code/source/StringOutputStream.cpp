#include "StringOutputStream.h"

void StringOutputStream::put(char c) {
    content += c;
}

void StringOutputStream::write(const std::string& s) {
    content += s;
}