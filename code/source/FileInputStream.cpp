#include "FileInputStream.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

FileInputStream::FileInputStream(const std::string& filename) {
    fileStream.open(filename);
    if (!fileStream) 
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

FileInputStream::~FileInputStream() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

int FileInputStream::get() {
    return fileStream.get();
}

bool FileInputStream::eof() {
    return fileStream.eof();
}

void FileInputStream::close() {
    if (fileStream.is_open()) 
    {
        fileStream.close();
    }
}