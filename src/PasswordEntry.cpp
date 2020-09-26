#include "PasswordEntry.h"

PasswordEntry::PasswordEntry
(
    std::string username,
    std::string password,
    std::string website
) : m_username(username), m_password(password), m_website(website)
{
}
