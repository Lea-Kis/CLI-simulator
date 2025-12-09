#include "CommandMaker.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "EchoCommand.h"
#include "WcCommand.h" 
#include "TouchCommand.h"
#include "RmCommand.h"
#include "BatchCommand.h"
#include "PromptCommand.h"
#include "HeadCommand.h"
#include "TrCommand.h"
#include "TruncateCommand.h"

#include <stdexcept>


Command* CommandMaker::create(const ParseResult& result) {
    switch (result.type) {
    case CommandType::Time:    return createTimeCommand(result);
    case CommandType::Date:    return createDateCommand(result);
    case CommandType::Echo:    return createEchoCommand(result);
    case CommandType::Wc:      return createWcCommand(result);
    case CommandType::Touch:   return createTouchCommand(result);
    case CommandType::Rm:      return createRmCommand(result);
    case CommandType::Truncate:return createTruncateCommand(result);
    case CommandType::Batch:   return createBatchCommand(result);
    case CommandType::Prompt:  return createPromptCommand(result);
    case CommandType::Head:    return createHeadCommand(result);
    case CommandType::Tr:      return createTrCommand(result);

    default: return nullptr;
    }
}

Command* CommandMaker::createTimeCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Time command does not accept options");
    }
    return new TimeCommand();
}

Command* CommandMaker::createDateCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Date command does not accept options");
    }
    return new DateCommand();
}

Command* CommandMaker::createEchoCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Echo command does not accept options");
    }
    return new EchoCommand();

}

Command* CommandMaker::createWcCommand(const ParseResult& result) {
    if (result.option != "-w" && result.option != "-c")
    {
        throw std::invalid_argument("Unknown option");
    }
    return new WcCommand(result.option);
}

Command* CommandMaker::createTouchCommand(const ParseResult& result){
    if (!result.option.empty())
    {
        throw std::logic_error("Touch command does not accept options");
    }
    if (result.inputFile.empty())
    {
        throw std::invalid_argument("Touch command requires a filename");
    }
    return new TouchCommand(result.inputFile);
}

Command* CommandMaker::createRmCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Rm command does not accept options");
    }
    if (result.inputFile.empty())
    {
        throw std::invalid_argument("Rm command requires a filename");
    }
    return new RmCommand(result.inputFile);
}

Command* CommandMaker::createTruncateCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Truncate command does not accept options");
    }
    if (result.inputFile.empty())
    {
        throw std::invalid_argument("Truncate command requires a filename");
    }
    return new TruncateCommand(result.inputFile);
}

Command* CommandMaker::createBatchCommand(const ParseResult& result){
    if (!result.option.empty())
    {
        throw std::logic_error("Batch command does not accept options");
    }
    return new BatchCommand();
}

Command* CommandMaker::createPromptCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Prompt command does not accept options");
    }
    if (result.arguments.empty())
    {
        throw std::invalid_argument("Prompt command requires an argument");
    }
    return new PromptCommand(result.arguments[0]);
}


Command* CommandMaker::createHeadCommand(const ParseResult& result){
    if (result.option.length() < 3 && result.option.substr(0, 2) != "-n")
    {
        throw std::invalid_argument("Invalid option");
    }
    return new HeadCommand(result.option);
}

Command* CommandMaker::createTrCommand(const ParseResult& result) {
    if (!result.option.empty())
    {
        throw std::logic_error("Tr command does not accept options");
    }
    if (result.arguments.empty())
    {
        throw std::invalid_argument("Tr command requires an argument");
    }
    return new TrCommand(result.arguments, result.inputStreamType);

}