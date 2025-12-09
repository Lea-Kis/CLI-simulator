#ifndef TouchCommand_h
#define TouchCommand_h

#include "Command.h"
#include <string>

class TouchCommand : public Command{
public:

	TouchCommand();
	TouchCommand(const std::string& s);
	void execute(InputStream& in, OutputStream& out) override;

private:
	std::string filename;
};

#endif