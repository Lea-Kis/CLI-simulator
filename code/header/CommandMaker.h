#ifndef CommandMaker_h
#define CommandMaker_h

#include "Command.h"
#include "Parser.h"

class CommandMaker {
public:
	static Command* create(const ParseResult& result);

private:
    static Command* createTimeCommand(const ParseResult& result);
    static Command* createDateCommand(const ParseResult& result);
    static Command* createEchoCommand(const ParseResult& result);
    static Command* createWcCommand(const ParseResult& result);
    static Command* createTouchCommand(const ParseResult& result);
    static Command* createRmCommand(const ParseResult& result);
    static Command* createTruncateCommand(const ParseResult& result);
    static Command* createBatchCommand(const ParseResult& result);
    static Command* createPromptCommand(const ParseResult& result);
    static Command* createHeadCommand(const ParseResult& result);
    static Command* createTrCommand(const ParseResult& result);
};
#endif