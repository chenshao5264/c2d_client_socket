#include "Crypto.h"

#include "aes.h"
using namespace std;
using namespace CryptoPP;

void Crypto::encrypt(const char * src, size_t len, char ** desc)
{
//     AESEncryption aesEncryptor; // ������
// 
//     unsigned char aesKey[AES::DEFAULT_KEYLENGTH]; // ��Կ
//     unsigned char inBlock[AES::BLOCKSIZE] = "123456789"; // Ҫ���ܵ����ݿ�
//     unsigned char outBlock[AES::BLOCKSIZE]; // ���ܺ������
//     unsigned char xorBlock[AES::BLOCKSIZE]; // ����Ϊȫ��
// 
//     memset(xorBlock, 0, AES::BLOCKSIZE);
// 
//     aesEncryptor.SetKey(aesKey, AES::DEFAULT_KEYLENGTH); // ���ü�����Կ
//     aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);
// 
//     *desc = (char*)outBlock;
}

void Crypto::decrypt(const char * src, size_t len, char ** desc)
{
    *desc = const_cast<char*>(src);
}
