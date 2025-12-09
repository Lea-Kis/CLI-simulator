#ifndef StringInputString_h
#define StringInputStream_h

#include "InputStream.h"
#include <string>
#include <sstream>

class StringInputStream : public InputStream {
private:
    std::istringstream stringStream;

public:

    StringInputStream(const std::string& content);
    ~StringInputStream() override = default;

    int get() override;
    bool eof() override;
};

#endif