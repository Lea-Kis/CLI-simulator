#ifndef Command_h
#define Command_h

class InputStream;
class OutputStream;

class Command {
public:

	virtual void execute(InputStream& in, OutputStream& out) = 0;
	virtual ~Command() {}
	Command() {}
};

#endif