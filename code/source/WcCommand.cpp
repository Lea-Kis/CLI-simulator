#include "WcCommand.h"
#include "InputStream.h"
#include "OutputStream.h"
#include <string>


WcCommand::WcCommand(const std::string& option): option(option){}

void WcCommand::execute(InputStream& in, OutputStream& out)
{
	int result = 0;
	std::string InputLines = in.readLines();
	if (option == "-w") result = numOfWords(InputLines);
	else if (option == "-c") result = numOfChars(InputLines);
	std::string res_string = std::to_string(result);
	out.write(res_string);
	out.put('\n');
}

int WcCommand::numOfWords(std::string line)
{
	int result = 0;
	std::string currLine;
	for (char c : line)
	{
		if (isspace(c) && !currLine.empty())
		{
			result++;
			currLine.clear();
		}
		else if (!isspace(c)) currLine += c;
	}
	if (!currLine.empty()) result++;
	return result;
}

int WcCommand::numOfChars(std::string line)
{
	int result = line.length();
	return result;
}