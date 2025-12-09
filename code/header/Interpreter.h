#ifndef Interpreter_h
#define Interpreter_h

#include <string>
#include "Parser.h"

class Parser;
class ErrorHandler;
struct ParseResult;
class InputStream;
class OutputStream;


class Interpreter {
public:

	static Interpreter* Instance();

	void run();
	void processCommandLine(const std::string& line, OutputStream* customOutput = nullptr);
	void setPrompt(const std::string& newPrompt);
	std::string getPrompt() const;

private:

	Interpreter();
	void executeCommand(const ParseResult& result);
	void executePipeline(const PipelineResult& pipeline, OutputStream* custom = nullptr);
	std::string currentPrompt;

	Interpreter(const Interpreter&) = delete; 
	Interpreter& operator = (const Interpreter&) = delete;
};

inline std::string Interpreter::getPrompt() const {
	return currentPrompt;
}

#endif