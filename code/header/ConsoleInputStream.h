#ifndef ConsoleInputStream_h
#define ConsoleInputStream_h

#include "InputStream.h"
#include <iostream>

class ConsoleInputStream : public InputStream {
public:
	virtual int get() override;
	virtual bool eof() override;
	ConsoleInputStream() = default;
	~ConsoleInputStream() override = default;
};

#endif