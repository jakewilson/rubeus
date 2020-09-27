#include "Logger.hpp"

#include <ctime>
#include <string>

Logger::Logger()
{
    m_handle.open(m_filename);
}

Logger::~Logger()
{
    m_handle.close();
}

void Logger::log(const char* str)
{
    if (str == NULL)
        return;

    time_t now = time(0);
    std::string timestamp {ctime(&now)};
    auto newline_pos = timestamp.find_last_of("\n");

    m_handle << "[" << timestamp.substr(0, newline_pos) << "] " << str << "\n";
    m_handle.flush();
}
