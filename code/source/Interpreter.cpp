#include "Interpreter.h"
#include "Parser.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "ConsoleOutputStream.h"
#include "OutputStream.h"
#include "InputStream.h"
#include "CommandMaker.h"
#include "ConsoleInputStream.h"
#include "StringInputStream.h"
#include "StringOutputStream.h"
#include <iostream>


Interpreter* Interpreter::Instance() {
	static Interpreter instance;
	return &instance;
}

Interpreter::Interpreter() : currentPrompt("$")
{}

void Interpreter::processCommandLine(const std::string& line, OutputStream* customOutput) {
	Parser parser;

	try {
		if (line.find('|') != std::string::npos) 
		{
			PipelineResult pipeline = parser.parsePipeline(line);
			if (!pipeline.isValid()) 
			{
				throw std::invalid_argument("Invalid pipeline");
			}
			executePipeline(pipeline, customOutput);
			return;
		}

		ParseResult result = parser.parse(line);
		if (!result.isValid()) 
		{
			throw std::invalid_argument("Invalid command");
		}

		if (customOutput && !result.outputRedirected) 
		{
			InputStream* input = nullptr;
			Command* cmd = nullptr;
			try {
				input = InputStream::createInputStream(result);
				cmd = CommandMaker::create(result);
				if (!cmd) throw std::runtime_error("Unknown command");
				if (!input) throw std::runtime_error("Failed to create input stream");

				cmd->execute(*input, *customOutput);

				delete input;
				delete cmd;
			}
			catch (...) {
				delete input;
				delete cmd;
				throw;
			}
		}
		else 
		{
			executeCommand(result);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Unknown error\n";
	}
}


void Interpreter::run() {
	Parser parser;
	ConsoleInputStream input;
	ConsoleOutputStream output;
	
	std::string line;
	
	while (true)
	{
		output.write(currentPrompt);
		output.put(' ');
		line = input.readLine();
		if (input.eof())
		{
			std::cin.clear();
			continue;
		}
		processCommandLine(line);
	}
}

void Interpreter::executeCommand(const ParseResult& result) {
	InputStream* input = nullptr;
	OutputStream* output = nullptr;
	Command* cmd = nullptr;

	try {
		input = InputStream::createInputStream(result);
		output = OutputStream::createOutputStream(result);

		if (!input) 
		{
			throw std::runtime_error("Failed to create input stream.");
		}
		if (!output)
		{
			delete input;
			throw std::runtime_error("Failed to create output stream.");
		}

		cmd = CommandMaker::create(result);
		if (!cmd) 
		{
			delete input;
			delete output;
			throw std::runtime_error("Unknown command");
		}

		cmd->execute(*input, *output);

		std::cin.clear();

		delete cmd;
		delete input;
		delete output;
	}
	catch (...) {
		delete cmd;
		delete input;
		delete output;
		throw;
	}
}


void Interpreter::executePipeline(const PipelineResult& pipeline, OutputStream* customOutput) {
	if (!pipeline.isValid()) return;
	std::string previousOutput;

	for (size_t i = 0; i < pipeline.commands.size(); i++)
	{
		const ParseResult& result = pipeline.commands[i];
		InputStream* input = nullptr;
		StringOutputStream* stringOutput = nullptr;
		OutputStream* output = nullptr;
		Command* cmd = nullptr;

		try {
			if (i == 0) input = InputStream::createInputStream(result);
			else input = new StringInputStream(previousOutput);

			if (i == pipeline.commands.size() - 1)
			{
				if (customOutput) output = customOutput;
				else output = OutputStream::createOutputStream(result);
			}
			else
			{
				stringOutput = new StringOutputStream();
				output = stringOutput;
			}
			cmd = CommandMaker::create(result);
			if (cmd && input && output) cmd->execute(*input, *output);
			if (i < pipeline.commands.size() - 1)
			{
				previousOutput = stringOutput->getContent();
			}

			delete cmd;
			delete input;
			if (i < pipeline.commands.size() - 1 || !customOutput) delete output;
			cmd = nullptr;
			input = nullptr;
			output = nullptr;
		}
		catch (...) {
			delete cmd;
			delete input;
			if (output && (i < pipeline.commands.size() - 1 || !customOutput)) delete output;
			throw;
		}
	}
}


void Interpreter::setPrompt(const std::string& newPrompt) {
	currentPrompt = newPrompt;
}