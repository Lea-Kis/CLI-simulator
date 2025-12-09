#ifndef FileOutputStream_h
#define FileOutputStream_h

#include "OutputStream.h"
#include <fstream>
#include <string>

class FileOutputStream : public OutputStream {
private:
    std::ofstream fileStream;

public:
    FileOutputStream(const std::string& filename, bool append = false);
    ~FileOutputStream() override;

    void put(char c) override;
};

#endif
