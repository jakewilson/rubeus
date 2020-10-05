#include "crypto.hpp"

#include <openssl/evp.h>

#ifdef __cplusplus
extern "C" {
#endif 

#include <scrypt-kdf.h>

#ifdef __cplusplus
}
#endif 

namespace crypto
{
constexpr int N = 1 << 19;
constexpr int r = 8;
constexpr int p = 1;

int derive_key(std::string password, char *key)
{
    uint8_t output[key_len];

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
        key_len
    );

    if (!rc)
    {
        for (auto i = 0; i < key_len; i++)
        {
            key[i] = static_cast<char>(output[i]);
        }
    }

    return rc;
}

void encrypt_str(
    const unsigned char *key,
    std::string plaintext,
    unsigned char *ciphertext
)
{
    // TODO change this to be random
    unsigned char *iv = (unsigned char *)"0123456789012345";
    unsigned char *ptext = (unsigned char *)plaintext.c_str();
    int len = aes_256_encrypt(ptext, plaintext.length(), key, iv, ciphertext);
}

int aes_256_encrypt(
    const unsigned char *plaintext,
    int plaintext_len,
    const unsigned char *key,
    const unsigned char *iv,
    unsigned char *ciphertext
)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handle_error("cipher_ctx_new");

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handle_error("encrypt init");

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handle_error("encrypt update");
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handle_error("encrypt final");
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

void decrypt_str(
    const unsigned char *key,
    std::string ciphertext,
    unsigned char *plaintext
)
{
    // TODO change this to be the first 16 bytes of the encrypted str
    unsigned char *iv = (unsigned char *)"0123456789012345";
    unsigned char *ctext = (unsigned char *)ciphertext.c_str();
    int len = aes_256_decrypt(ctext, ciphertext.length(), key, iv, plaintext);
}


int aes_256_decrypt(
    const unsigned char *ciphertext,
    int ciphertext_len,
    const unsigned char *key,
    const unsigned char *iv,
    unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handle_error("cipher_ctx_new");

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handle_error("decrypt init");

    /*
     * Provide the message to be decrypted, and obtain the decrypted output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handle_error("decrypt update");
    plaintext_len = len;

    /*
     * Finalise the decryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handle_error("decrypt final");
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;

}

void handle_error(const char *msg)
{
    throw encrypt_exception(msg);
}


}
