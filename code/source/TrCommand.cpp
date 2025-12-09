#include "TrCommand.h"
#include "InputStream.h"
#include "OutputStream.h"
#include <stdexcept>

TrCommand::TrCommand(std::vector<std::string> arguments, InputStreamSource input) {
	if (arguments.size() == 1)
	{
		what = arguments[0];
		swap = false;
	}
	else if (arguments.size() == 2)
	{
		if (input == InputStreamSource::ArgumentFile || input == InputStreamSource::RedirectionFile)
		{
			what = arguments[0];
			with = arguments[1];
			swap = false;
		}
		else
		{
			what = arguments[1];
			help = arguments[0];
		}
	}
	else if (arguments.size() == 3)
	{
		what = arguments[1];
		with = arguments[2];
		help = arguments[0];
	}

	if (arguments.size() > 3)
	{
		throw std::runtime_error("Too many arguments.");
	}
}

void TrCommand::execute(InputStream& in, OutputStream& out) {
	argument = in.readLines();
	if (help != argument && swap)
	{
		with = what;
		what = help;
	}
	if (argument.empty() || what.empty())
	{
		throw std::runtime_error("Missing argument.");
	}
	std::string replace = (with.empty())? std::string() : with;
	std::string output;
	std::size_t pos = 0;

	while (true)
	{
		std::size_t found = argument.find(what, pos);
		if (found == std::string::npos)
		{
			output.append(argument, pos, std::string::npos);
			break;
		}
		output.append(argument, pos, found - pos);
		output.append(replace);
		pos = found + what.size();
	}
	out.write(output);
	out.put('\n');
}