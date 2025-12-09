#include "RmCommand.h"
#include <iostream>
#include <cstdio>
#include <fstream>

RmCommand::RmCommand(const std::string& filename) : filename(filename) {}

void RmCommand::execute(InputStream& in, OutputStream& out) {
    std::ifstream check(filename);
    if (!check.is_open()) {
        throw std::runtime_error("File '" + filename + "' does not exist");
    }
    check.close();

    if (std::remove(filename.c_str()) != 0) {
        throw std::runtime_error("Could not delete file '" + filename + "'");
    }
}