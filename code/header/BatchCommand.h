#ifndef BatchCommand_h
#define BatchCommand_h

#include "Command.h"
#include <string>

class BatchCommand : public Command {
public:
    BatchCommand();
    void execute(InputStream& in, OutputStream& out) override;

private:
    std::string argument;

};

#endif
