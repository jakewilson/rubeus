#pragma once

#include <string>
#include <exception>

namespace crypto
{
    int derive_key(std::string, char *key);
    constexpr int output_len = 16;

    struct crypto_exception : public std::exception
    {
        crypto_exception(const char *msg) : m_msg(msg) {}
        const char * what() const throw ()
        {
            return m_msg;
        }
        const char *m_msg;
    };
};

