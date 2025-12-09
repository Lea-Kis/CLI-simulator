#include "PromptCommand.h"
#include "Interpreter.h"

PromptCommand::PromptCommand(const std::string& prompt) : newPrompt(prompt) {}

void PromptCommand::execute(InputStream& in, OutputStream& out) {
    Interpreter::Instance()->setPrompt(newPrompt);
}