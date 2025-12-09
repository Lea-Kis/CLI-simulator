#ifndef StringOutputStream_h
#define StringOutputStream_h

#include "OutputStream.h"
#include <string>

class StringOutputStream : public OutputStream {
private:
    std::string content;

public:
    StringOutputStream() : content("") {}
    ~StringOutputStream() override = default;

    void put(char c) override;
    void write(const std::string& s) override;
    std::string getContent() { return content; };
};

#endif