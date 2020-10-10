#pragma once

#include <exception>
#include <string>

namespace crypto
{
    constexpr int key_len = 32;
    constexpr int block_size = 16;

    int derive_key(std::string, char *);
    void encrypt_str(const unsigned char *, std::string, unsigned char *);
    int aes_256_encrypt(const unsigned char *, int, const unsigned char *,
                        const unsigned char *, unsigned char *);

    void decrypt_str(const unsigned char *, std::string, unsigned char *);
    int aes_256_decrypt(const unsigned char *, int, const unsigned char *,
                        const unsigned char *, unsigned char *);
    void handle_error(const char *);
    struct encrypt_exception : public std::exception
    {
        encrypt_exception(const char *msg) : m_msg(msg) {}
        const char * what() const throw() {
            return m_msg;
        }
        const char *m_msg;
    };
};

