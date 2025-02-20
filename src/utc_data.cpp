#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "utc_data.h"

std::string get_utc_time() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    tm utc_time_struct;

    tm* utc_time = nullptr;
    #if defined(__APPLE__) || defined(__linux__)  // POSIX platforms (macOS, Linux)
        utc_time = gmtime_r(&t_c, &utc_time_struct);
    #elif defined(_WIN32)  // Windows
        gmtime_s(&utc_time_struct, &t_c);  // gmtime_s does not return a pointer
        utc_time = &utc_time_struct;
    #endif

    std::ostringstream oss;
    oss << 1900 + utc_time->tm_year << "-"
            << 1 + utc_time->tm_mon << "-"
            << utc_time->tm_mday << "T"
            << utc_time->tm_hour << ":"
            << utc_time->tm_min << ":"
            << utc_time->tm_sec << std::endl;
    return oss.str();
}