#include "RubeusCommand.hpp"

#include <sstream>

RubeusCommand::RubeusCommand(const int key, const std::string description)
    : m_key(key), m_description(description)
{
}

std::string RubeusCommand::to_str()
{
    // TODO if char is a visible char, don't use the map
    auto desc = key_desc_map[m_key];
    std::stringstream ss;
    ss << "[" << desc << "] " << m_description;
    return ss.str();
}
