#include "crypto.hpp"

#ifdef __cplusplus
extern "C" {
#endif 

#include <scrypt-kdf.h>

#ifdef __cplusplus
}
#endif 

namespace crypto
{
constexpr int N = 16384;
constexpr int r = 8;
constexpr int p = 1;

int derive_key(std::string password, char *key)
{
    uint8_t output[output_len];

    const char *salt = "rubeus";

    auto rc = scrypt_kdf(
        (const uint8_t *)password.c_str(),
        password.length(),
        (const uint8_t *)salt,
        strlen(salt),
        N,
        r,
        p,
        output,
        output_len
    );

    if (!rc)
    {
        for (auto i = 0; i < output_len; i++)
        {
            key[i] = static_cast<char>(output[i]);
        }
    }

    return rc;
}

}
