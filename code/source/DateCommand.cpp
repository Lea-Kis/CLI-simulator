#include "DateCommand.h"
#include "OutputStream.h"
#include "Parser.h"
#include <chrono>
#include <iomanip>

void DateCommand::execute(InputStream& in, OutputStream& out) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_time);

    char dateString[11];
    std::strftime(dateString, sizeof(dateString), "%Y-%m-%d", &now_tm);

    out.write(dateString);
    out.put('\n');
}