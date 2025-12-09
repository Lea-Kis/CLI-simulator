#include "TimeCommand.h"
#include "OutputStream.h"
#include <iostream>
#include <chrono>
#include <iomanip>

void TimeCommand::execute(InputStream& in, OutputStream& out) {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
	localtime_s(&now_tm, &now_time);

	char timeString[9];
	std::strftime(timeString, sizeof(timeString), "%H:%M:%S", &now_tm);

	out.write(timeString);
	out.put('\n');
}