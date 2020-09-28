#include "PasswordEntry.hpp"

PasswordEntry::PasswordEntry
(
    int id,
    std::string username,
    std::string password,
    std::string title
) : m_id(id), m_username(username), m_password(password), m_title(title)
{
}
