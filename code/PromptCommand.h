#ifndef PromptCommand_h
#define PromptCommand_h

#include "Command.h"
#include <string>

class PromptCommand : public Command {
public:
    PromptCommand(const std::string& prompt);
    void execute(InputStream& in, OutputStream& out) override;

private:
    std::string newPrompt;

};

#endif