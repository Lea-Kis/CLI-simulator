#include "OutputStream.h"
#include "ConsoleOutputStream.h"
#include "FileOutputStream.h"
#include "Parser.h"
#include <iostream>

void OutputStream::write(const std::string& s) {
    for (char c : s) {
        this->put(c);
    }
}

OutputStream* OutputStream::createOutputStream(const ParseResult& result) {
    switch (result.outputStreamType) {
    case OutputStreamSource::Default:
        return new ConsoleOutputStream();
    case OutputStreamSource::RedirectionFile:
        return new FileOutputStream(result.outputFile, result.outputAppend);
    default:
        return nullptr;
    }
}