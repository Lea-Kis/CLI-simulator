#ifndef DateCommand_h
#define DateCommand_h

#include "Command.h"

class DateCommand : public Command {
public:
	DateCommand() = default;
	virtual void execute(InputStream& in, OutputStream& out) override;
};

#endif