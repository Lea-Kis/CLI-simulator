#ifndef WcCommand_h
#define WcCommand_h

#include "Command.h"
#include "Parser.h"
#include <string>

class WcCommand : public Command
{
public:
	WcCommand(const std::string& option);
	void execute(InputStream& in, OutputStream& out) override;

private:
	std::string option;
	int numOfWords(std::string line);
	int numOfChars(std::string line);
};

#endif
