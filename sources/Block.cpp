#include <Block.h>
#include <stdio.h>
#include <cstring>

Block::Block(uint32_t p_block_size)
{
    block_size = p_block_size;
    read_size = 0;
    buffer = (char *)calloc(block_size + 1 + (block_size - (block_size % CryptoPP::AES::BLOCKSIZE)), sizeof(char));
}
bool Block::load(fstream &f)
{
    if (f.is_open())
    {
        f.read(buffer, block_size);
        read_size = f.gcount();
        if (f || f.gcount() > 0)

            return true;
        else
            return false;
    }
    else
        return false;
}
bool Block::store(fstream &f)
{
    if (f.is_open())
    {
        f.write(buffer, read_size);
        return true;
    }
    else
        return false;
}

void Block::encrypt(CryptoPP::byte *key, CryptoPP::byte *iv)
{
    string ciphertext;
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put((const unsigned char *) buffer , strlen(buffer));
    read_size = ciphertext.size();
    memcpy(buffer, ciphertext.c_str(), read_size);
    stfEncryptor.MessageEnd(); 

}

void Block::decrypt(CryptoPP::byte *key, CryptoPP::byte *iv)
{
    string decryptedtext;
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
    stfDecryptor.Put((const unsigned char*)decryptedtext.c_str() , decryptedtext.size() );
    read_size = decryptedtext.size();
    memcpy(buffer, decryptedtext.c_str(), read_size);
    stfDecryptor.MessageEnd();
}  
void Block::print()
{
    cout << buffer;
}
Block::~Block()
{
    if (buffer != NULL)
        free(buffer);
}
