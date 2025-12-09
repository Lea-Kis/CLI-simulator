#include "EchoCommand.h"
#include "InputStream.h"
#include "OutputStream.h"
#include <string>


EchoCommand::EchoCommand() {}

void EchoCommand::execute(InputStream& in, OutputStream& out)
{
	std::string InputLines = in.readLines();
	out.write(InputLines);
	out.put('\n');
}