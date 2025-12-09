#ifndef TruncateCommand_h
#define TruncateCommand_h

#include "Command.h"
#include "InputStream.h"
#include "OutputStream.h"
#include <string>

class TruncateCommand : public Command {
public:
	TruncateCommand(const std::string& filename);
	void execute(InputStream& in, OutputStream& out);

private:
	std::string filename;
};

#endif