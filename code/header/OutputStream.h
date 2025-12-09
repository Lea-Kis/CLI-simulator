#ifndef OutputStream_h
#define OutputStream_h

#include <string>
#include"Parser.h"

class OutputStream {
public:

	virtual void put(char c) = 0;

	virtual void write(const std::string& s);

	static OutputStream* createOutputStream(const struct ParseResult& result);

	virtual ~OutputStream() {}

protected:

	OutputStream() {}

};
#endif