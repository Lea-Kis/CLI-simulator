#ifndef InputStream_h
#define InputStream_h

#include<string>
#include"Parser.h"

class InputStream {
public:

	virtual int get() = 0;
	virtual bool eof() = 0;

	virtual std::string readLine();
	virtual std::string readLines();
	static InputStream* createInputStream(const struct ParseResult& result);

	virtual ~InputStream() {}

protected:

	InputStream() = default;
};

#endif