#ifndef __Crypto_H__
#define __Crypto_H__


class Crypto
{
public:
    static void encrypt(const char* src, size_t len, char** desc);
    static void decrypt(const char* src, size_t len, char** desc);
};

#endif
