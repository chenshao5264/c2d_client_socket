#include "Crypto.h"

#include "aes.h"
using namespace std;
using namespace CryptoPP;

void Crypto::encrypt(const char * src, size_t len, char ** desc)
{
//     AESEncryption aesEncryptor; // 加密器
// 
//     unsigned char aesKey[AES::DEFAULT_KEYLENGTH]; // 密钥
//     unsigned char inBlock[AES::BLOCKSIZE] = "123456789"; // 要解密的数据块
//     unsigned char outBlock[AES::BLOCKSIZE]; // 加密后的密文
//     unsigned char xorBlock[AES::BLOCKSIZE]; // 必须为全零
// 
//     memset(xorBlock, 0, AES::BLOCKSIZE);
// 
//     aesEncryptor.SetKey(aesKey, AES::DEFAULT_KEYLENGTH); // 设置加密密钥
//     aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);
// 
//     *desc = (char*)outBlock;
}

void Crypto::decrypt(const char * src, size_t len, char ** desc)
{
    *desc = const_cast<char*>(src);
}
