#ifndef HeadCommand_h
#define HeadCommand_h

#include "Command.h"
#include <string>

class HeadCommand : public Command {
public:
    HeadCommand(std::string option);
    void execute(InputStream& in, OutputStream& out) override;

private:
    int lineCount = 0;
    std::string option;
    std::string argument;

};

#endif