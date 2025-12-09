#include "TruncateCommand.h"
#include <fstream>

TruncateCommand::TruncateCommand(const std::string& filename) : filename(filename) {}

void TruncateCommand::execute(InputStream& in, OutputStream& out){
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Could not truncate file:" + filename);
    }
    file.close();
}