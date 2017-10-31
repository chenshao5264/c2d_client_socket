#include "Crypto.h"

void Crypto::encrypt(const char * src, size_t len, char ** desc)
{
    *desc = const_cast<char*>(src);
}

void Crypto::decrypt(const char * src, size_t len, char ** desc)
{
    *desc = const_cast<char*>(src);
}
