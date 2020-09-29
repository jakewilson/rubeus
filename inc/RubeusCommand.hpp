#include <string>
#include <unordered_map>

struct RubeusCommand
{
    RubeusCommand(const int, const std::string);

    std::string to_str();

    const int m_key;
    const std::string m_description;
};

static std::unordered_map<int, std::string> key_desc_map =
{
    { 27, "esc"}
};
