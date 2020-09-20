#pragma once

#include <string>

class PasswordEntry
{
public:
    PasswordEntry(std::string username, std::string password, std::string website);
    ~PasswordEntry() {}

    std::string get_username() { return m_username; }
    std::string get_password() { return m_password; }

private:
    int m_id; // TODO should likely be const

    std::string m_username {};
    std::string m_password {};

    std::string m_website {};
};
