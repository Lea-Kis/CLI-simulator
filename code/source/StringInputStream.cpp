#include "StringInputStream.h"
#include <sstream>

StringInputStream::StringInputStream(const std::string& content) : stringStream(content) {}

int StringInputStream::get() {
    return stringStream.get();
}

bool StringInputStream::eof() {
    return stringStream.eof();
}