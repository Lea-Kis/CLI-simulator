#include "Parser.h"
#include <cctype>
#include <stdexcept>

ParseResult Parser::parse(const std::string& line) {
	ParseResult result;

	auto tokens = tokenize(line);
	if (containsPipe(tokens)) {
		result.type = CommandType::Unknown;
		return result;
	}
	detectRedirection(tokens, result);
	fillParseResult(tokens, result);
	return result;
}

std::vector<Token> Parser::tokenize(const std::string& line) {
	std::vector<Token> tokens;
	std::string tok;
	bool inQuotes = false;
	for (size_t i=0; i<line.length(); i++) 
	{
		if (line[i] == '"')
		{
			inQuotes = !inQuotes;
			if (!inQuotes) { tokens.push_back(Token{tok, true}); tok.clear(); }
		}
		else if (!inQuotes && isspace(line[i]))
		{
			if (!tok.empty()) { tokens.push_back(Token{tok, false}); tok.clear(); }
		}
		else if (!inQuotes && (line[i] == '<' || line[i] == '|'))
		{
			if (!tok.empty()) { tokens.push_back(Token{tok, false}); tok.clear(); }
			std::string s(1, line[i]);
			tokens.push_back(Token{s, false});
		}
		else if (!inQuotes && line[i] == '>')
		{
			if (!tok.empty()) { tokens.push_back(Token{ tok, false }); tok.clear(); }
			tok += line[i];
			if (i < (line.length() - 1) && line[i + 1] == '>')
			{
				tok += line[i + 1];
				i++;
			}
			tokens.push_back(Token{ tok, false });
			tok.clear();
		}
		else tok += line[i];
	}
	if (!tok.empty()) tokens.push_back(Token{tok, false});
	return tokens;
}


void Parser::detectRedirection(std::vector<Token>& tokens, ParseResult& res) {
	for (size_t i = 0; i < tokens.size();) {
		if (tokens[i].text == "<") 
		{
			i = handleInputRedirection(tokens, res, i);
		}
		else if (tokens[i].text == ">") 
		{
			i = handleOutputRedirection(tokens, res, i, false);
		}
		else if (tokens[i].text == ">>") 
		{
			i = handleOutputRedirection(tokens, res, i, true);
		}
		else i++;
	}
}


size_t Parser::handleInputRedirection(std::vector<Token>& tokens, ParseResult& res, size_t i) {
	if (i + 1 < tokens.size()) 
	{
		res.inputRedirected = true;
		res.inputFile = tokens[i + 1].text;
		res.inputStreamType = InputStreamSource::RedirectionFile;
		tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
		return i;
	}
	else 
	{
		throw std::runtime_error("Input redirection without filename");
	}
}


size_t Parser::handleOutputRedirection(std::vector<Token>& tokens, ParseResult& res, size_t i, bool append) {
	if (i + 1 < tokens.size()) 
	{
		res.outputRedirected = true;
		res.outputAppend = append;
		res.outputFile = tokens[i + 1].text;
		res.outputStreamType = OutputStreamSource::RedirectionFile;
		tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
		return i;
	}
	else 
	{
		throw std::runtime_error("Output redirection without filename");
	}
}


void Parser::fillParseResult(const std::vector<Token>& tokens, ParseResult& res) {
	if (tokens.empty()) return;
	res.type = determineCommandType(tokens[0].text);
	if (res.type == CommandType::Unknown) throw std::runtime_error("Invalid command.");
	size_t index = 1;
	if (commandExpectsOption(res.type)) 
	{
		fillOption(index, tokens, res);
	}
	if (commandExpectsArgument(res.type)) 
	{
		if (tokens.size() == 2 && res.type == CommandType::Tr);
		else
		{
			fillArgument(index, tokens, res);
		}
	}
	checkRedirectionConflict(res);
	if (index < tokens.size() && res.type!= CommandType::Tr)
	{
		throw std::runtime_error("Too many arguments for command");
	}
	else if (index < tokens.size() && res.type == CommandType::Tr)
	{
		while (index < tokens.size())
		{
			if (tokens[index].quoted)
			{
				res.arguments.push_back(tokens[index].text);
			}
			index++;
		}
	}
}


void Parser::fillOption(size_t& index, const std::vector<Token>& tokens, ParseResult& res)
{
	if (index < tokens.size()) 
	{
		res.option = tokens[index++].text;
	}
	else 
	{
		throw std::runtime_error("Missing required option for command");
	}
}

void Parser::fillArgument(size_t& index, const std::vector<Token>& tokens, ParseResult& res)
{
	if (index < tokens.size() && !res.inputRedirected)
	{
		if (tokens[index].quoted)
		{
			res.arguments.push_back(tokens[index].text);
			res.inputStreamType = InputStreamSource::ArgumentString;
		}
		else
		{
			res.inputFile = tokens[index].text;
			res.inputStreamType = InputStreamSource::ArgumentFile;
		}
		index++;
	}
	else if (commandRequiresArgument(res.type) && !res.inputRedirected)
	{
		throw std::runtime_error("Missing required argument for command");
	}
}


void Parser::checkRedirectionConflict(ParseResult& res) {
	if (!res.arguments.empty() && res.inputRedirected) {
		throw std::runtime_error("Redirection conflict");
	}
	return;
}


bool Parser::commandExpectsOption(CommandType type) {
	switch (type) 
	{
		case CommandType::Wc: return true;
		case CommandType::Head: return true;
		default: return false;
	}
}

bool Parser::commandExpectsArgument(CommandType type) {
	switch (type) 
	{
		case CommandType::Echo: return true;
		case CommandType::Wc: return true;
		case CommandType::Touch: return true;
		case CommandType::Prompt: return true;
		case CommandType::Rm: return true;
		case CommandType::Truncate: return true;
		case CommandType::Batch: return true;
		case CommandType::Head: return true;
		case CommandType::Tr: return true;
		default: return false;
	}
}

bool Parser::commandRequiresArgument(CommandType type) {
	switch (type) {
	case CommandType::Touch: return true;
	case CommandType::Prompt: return true;
	case CommandType::Rm: return true;
	case CommandType::Truncate: return true;
	default:
		return false;
	}
}


bool Parser::containsPipe(std::vector<Token>& tokens) {
	for (const Token& token : tokens) 
	{
		if (token.text == "|") return true;
	}
	return false;
}


PipelineResult Parser::parsePipeline(const std::string& line) {
	PipelineResult result;

	std::vector<std::string> commandStrings;
	std::string current;

	for (char c : line) 
	{
		if (c == '|') 
		{
			if (!current.empty())
			{
				commandStrings.push_back(current);
				current.clear();
			}
			else result.valid = false;
		}
		else current += c;
	}
	if (!current.empty()) commandStrings.push_back(current);

	if (commandStrings.size() < 2) 
	{
		result.valid = false;
		return result;
	}

	for (const auto& cmdStr : commandStrings) 
	{
		ParseResult cmdResult = parse(cmdStr);
		if (!cmdResult.isValid()) 
		{
			result.valid = false;
			return result;
		}
		result.commands.push_back(cmdResult);
	}

	return result;
}


CommandType Parser::determineCommandType(const std::string& token) {
	auto it = commandMap.find(token);
	if (it != commandMap.end())
	{
		return it->second;
	}
	return CommandType::Unknown;
}


const std::unordered_map<std::string, CommandType> Parser::commandMap = {
	{"echo", CommandType::Echo},
	{"time", CommandType::Time},
	{"date", CommandType::Date},
	{"wc",   CommandType::Wc},
	{"touch", CommandType::Touch},
	{"prompt", CommandType::Prompt},
	{"truncate", CommandType::Truncate},
	{"rm", CommandType::Rm},
	{"batch", CommandType::Batch},
	{"prompt", CommandType::Prompt },
	{"tr", CommandType::Tr},
	{"head", CommandType::Head}
};