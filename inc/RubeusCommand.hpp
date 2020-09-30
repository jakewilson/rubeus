#pragma once

#include <string>
#include <unordered_map>

struct RubeusCommand
{
    RubeusCommand(const int, const std::string);

    std::string to_str() const;

    const int m_key;
    const std::string m_description;
};
