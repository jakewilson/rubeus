#pragma once

#include <fstream>
#include <string>

class Logger
{
public:
    Logger();
    ~Logger();
    void log(const char*);
    void operator<<(std::string str) { log(str.c_str()); };
    void operator<<(const char* str) { log(str); };

private:
    std::ofstream m_handle;

    const std::string m_filename { "rubeus.log" };
};

static Logger logger{};
