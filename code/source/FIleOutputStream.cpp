#include "FileOutputStream.h"
#include <fstream>
#include <stdexcept>

FileOutputStream::FileOutputStream(const std::string& filename, bool append) {
    std::ios::openmode mode = std::ios::out;
    if (append) 
    {
        mode |= std::ios::app; // Append mode
    }
    else 
    {
        mode |= std::ios::trunc; // Truncate mode (default for out)
    }
    fileStream.open(filename, mode);
    if (!fileStream) 
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}
    

FileOutputStream::~FileOutputStream() {
    if (fileStream.is_open()) 
    {
        fileStream.close();
    }
}

void FileOutputStream::put(char c) {
    if (fileStream.is_open()) 
    {
        fileStream.put(c);
    }
}