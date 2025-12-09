#ifndef RmCommand_h
#define RmCommanh_h

#include "Command.h"
#include "InputStream.h"
#include "OutputStream.h"
#include <string>

class RmCommand : public Command {
public:
	RmCommand(const std::string& filename);
	void execute(InputStream& in, OutputStream& out) override;

private:
	std::string filename;
};

#endif