#include "BatchCommand.h"
#include "Interpreter.h"
#include "Parser.h"
#include "InputStream.h"
#include "StringInputStream.h"
#include <iostream>

BatchCommand::BatchCommand() {}

void BatchCommand::execute(InputStream& in, OutputStream& out) {
    std::string batchContent;
    batchContent = in.readLines();

    StringInputStream batchInput(batchContent);

    while (!batchInput.eof()) 
    {
        std::string line = batchInput.readLine();
        if (!line.empty()) 
        {
            Interpreter::Instance()->processCommandLine(line, &out);
        }
    }
    std::cin.clear();
}