#include "TouchCommand.h"
#include "OutputStream.h"
#include <fstream>
#include <string>

TouchCommand::TouchCommand(){}

TouchCommand::TouchCommand(const std::string& s): filename(s) {}

void TouchCommand::execute(InputStream& in, OutputStream& out)
{
	std::ifstream check(this->filename, std::ios::in);
	if (check.is_open())
	{
		check.close();
		throw std::runtime_error("File '" + this->filename + "' already exists.");
	}
	std::ofstream fileStream(this->filename, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!fileStream.is_open())
	{
		throw std::runtime_error("Could not create file '" + this->filename + "'");
	}
}