#ifndef FileInputStream_h
#define FileInputStream_h

#include "InputStream.h"
#include <fstream>
#include <string>

class FileInputStream : public InputStream {
public:
    FileInputStream(const std::string& filename);
    ~FileInputStream() override;

    int get() override;
    bool eof() override;
    void close();

private:
    std::ifstream fileStream;

};

#endif