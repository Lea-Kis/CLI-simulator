#ifndef TrCommand_h
#define TrCommand_h

#include "Command.h"
#include "InputStream.h"
#include <string>
#include <vector>

class TrCommand : public Command {
public:
    TrCommand(std::vector<std::string> arguments, InputStreamSource inputsrc);
    void execute(InputStream& in, OutputStream& out) override;

private:
    std::string what;
    std::string with = "";
    std::string argument;
    std::string help = "";
    bool swap = true;

};

#endif