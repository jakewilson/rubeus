#include "RubeusCommand.hpp"

#include <sstream>

RubeusCommand::RubeusCommand(const int key, const std::string description)
    : m_key(key), m_description(description)
{
}

std::unordered_map<int, std::string> key_desc_map =
{
    { 27, "esc"}
};

std::string RubeusCommand::to_str() const
{
    std::string key_str {};
    if (m_key >= 32 && m_key <= 126)
    { 
        key_str = static_cast<char>(m_key);
    }
    else
    {
        key_str = key_desc_map[m_key];
    }

    std::stringstream ss;
    ss << "[" << key_str << "] " << m_description;
    return ss.str();
}
