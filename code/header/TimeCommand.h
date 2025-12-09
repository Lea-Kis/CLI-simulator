#ifndef TimeCommand_h
#define TimeCommand_h

#include "Command.h"

class TimeCommand : public Command {
public:

	TimeCommand() {}

	virtual void execute(InputStream& in, OutputStream& out) override;
};

#endif