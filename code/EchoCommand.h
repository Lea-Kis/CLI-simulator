#ifndef EchoCommand_h
#define EchoCommand_h

#include "Command.h"
#include <string>

class EchoCommand : public Command
{
public:
	EchoCommand();
	void execute(InputStream& in, OutputStream& out) override;

};

#endif