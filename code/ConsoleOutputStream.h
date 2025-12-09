#ifndef ConsoleOutputStream_h
#define ConsoleOutputStream_h

#include "OutputStream.h"
#include <iostream>


class ConsoleOutputStream : public OutputStream {
public:

	void put(char c) override;
	ConsoleOutputStream() {}
	~ConsoleOutputStream() {}
};

#endif
