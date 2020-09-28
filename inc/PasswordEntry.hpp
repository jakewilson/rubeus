#pragma once

#include <string>

class PasswordEntry
{
public:
    PasswordEntry(
        int id,
        std::string username,
        std::string password,
        std::string title
    );
    ~PasswordEntry() {}

    std::string get_username() const { return m_username; }
    std::string get_password() const { return m_password; }
    std::string get_title() const { return m_title; }

private:
    int m_id;

    std::string m_username {};
    std::string m_password {};

    std::string m_title {};
};
