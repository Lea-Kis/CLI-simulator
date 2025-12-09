#include "InputStream.h"
#include "Command.h"
#include "ConsoleInputStream.h"
#include "FileInputStream.h"
#include "StringInputStream.h"
#include "Parser.h"
#include <iostream> 
#include <fstream>
#include <string>
#include <stdexcept>

std::string InputStream::readLine() {
	std::string line;
	int c;
	while (true)
	{
		c = this->get();
        if (c == EOF || this->eof()) break;
		if (c == '\n') break;
		line += c;
	}
	return line;
}

std::string InputStream::readLines()
{
	std::string Lines;
	std::string inputLine;
	while (!eof())
	{
		inputLine = readLine();
		Lines += inputLine;
		if (!eof()) Lines += '\n';
	}
	return Lines;
}

InputStream* InputStream::createInputStream(const ParseResult& result) {
    switch (result.inputStreamType) {
    case InputStreamSource::Default:
        return new ConsoleInputStream();
    case InputStreamSource::ArgumentFile: {
        if (result.type == CommandType::Touch || result.type == CommandType::Rm)
        {
            return new StringInputStream(result.inputFile);
        }
        return new FileInputStream(result.inputFile);
    }
    case InputStreamSource::ArgumentString:
        if (result.arguments.empty()) 
        {
            throw std::invalid_argument("Missing argument string");
            //return new StringInputStream("");
        }
        return new StringInputStream(result.arguments[0]);
    case InputStreamSource::RedirectionFile:
        return new FileInputStream(result.inputFile);
    default:
        return nullptr;
    }
}
