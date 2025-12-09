#include "HeadCommand.h"
#include "InputStream.h"
#include "OutputStream.h"

#include <stdexcept>
#include <cctype>

#define buba bubica

HeadCommand::HeadCommand(std::string option): option(option) {}

void HeadCommand::execute(InputStream& in, OutputStream& out){
	std::string numberStr = option.substr(2);
    if (numberStr.empty() || numberStr.length() > 5) 
    {
        throw std::invalid_argument("Head command requires 1–5 digits after -n");
    }
    for (char c : numberStr) 
    {
        if (!std::isdigit(static_cast<unsigned char>(c))) 
        {
            throw std::invalid_argument("Head command requires digits after -n");
        }
    }
    int lineCount = std::stoi(numberStr);
    std::vector<std::string> content;
    std::string alllines = in.readLines();
    std::size_t pos = 0;
    while (pos < alllines.size()) 
    {
        std::size_t newline = alllines.find('\n', pos);
        if (newline == std::string::npos) 
        {
            content.push_back(alllines.substr(pos));
            break;
        }
        content.push_back(alllines.substr(pos, newline - pos));
        pos = newline + 1;
    }
    if (lineCount > (int)content.size()) lineCount = content.size();
    for (int i = 0; i < lineCount; i++)
    {
        if (!content[i].empty())
        {
            out.write(content[i]);
            out.put('\n');
        }
    }
}
