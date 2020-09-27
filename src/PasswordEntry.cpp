#include "PasswordEntry.hpp"

PasswordEntry::PasswordEntry
(
    int id,
    std::string username,
    std::string password,
    std::string website
) : m_id(id), m_username(username), m_password(password), m_website(website)
{
}
