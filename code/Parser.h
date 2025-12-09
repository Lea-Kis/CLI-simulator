#ifndef Parser_h
#define Parser_h

#include <string>
#include <vector>
#include <unordered_map>

class Command;

enum class CommandType {
	Echo, Time, Date, Wc, Touch, Prompt, Rm, Truncate, Batch, Head, Tr, Unknown
};

enum class InputStreamSource {
	Default, ArgumentFile, ArgumentString, RedirectionFile, Pipe
};

enum class OutputStreamSource {
	Default, RedirectionFile, Pipe
};

struct Token {
	std::string text;
	bool quoted = false;
};

struct ParseResult {
	CommandType type = CommandType::Unknown;

	std::vector<std::string> arguments;
	std::string option;

	InputStreamSource inputStreamType = InputStreamSource::Default;
	bool inputRedirected = false;
	std::string inputFile = "";

	OutputStreamSource outputStreamType = OutputStreamSource::Default;
	bool outputRedirected = false;
	std::string outputFile = "";
	bool outputAppend = false;

	std::string errorMessage;

	bool isValid() const { return type != CommandType::Unknown; }
};


struct PipelineResult {
	std::vector<ParseResult> commands;
	bool valid = true;

	bool isValid() const { return valid && commands.size() >= 2; }
};


class Parser {
public:

	Parser() = default;

	ParseResult parse(const std::string& line);
	PipelineResult parsePipeline(const std::string& line);


private:
	std::vector<Token> tokenize(const std::string& line);
	void detectRedirection(std::vector<Token>& tokens, ParseResult& res);
	void fillParseResult(const std::vector<Token>& tokens, ParseResult& res);
	void fillOption(size_t& index, const std::vector<Token>& tokens, ParseResult& res);
	void fillArgument(size_t& index, const std::vector<Token>& tokens, ParseResult& res);
	CommandType determineCommandType(const std::string& token);

	static const std::unordered_map<std::string, CommandType> commandMap;

	size_t handleInputRedirection(std::vector<Token>& tokens, ParseResult& res, size_t i);
	size_t handleOutputRedirection(std::vector<Token>& tokens, ParseResult& res, size_t i, bool append);
	void checkRedirectionConflict(ParseResult& res);

	bool commandExpectsOption(CommandType type);
	bool commandExpectsArgument(CommandType type);
	bool commandRequiresArgument(CommandType type);
	bool containsPipe(std::vector<Token>& tokens);

};

#endif
