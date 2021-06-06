#include <ShredManager.h>

ShredManager::ShredManager(char *p_file_name, uint16_t p_block_size, uint16_t p_shred_count, bool truncate)
{
    shred_count = p_shred_count;
    shreds = (Shred **)calloc(shred_count, sizeof(Shred *));
    for (char i = 0; i < shred_count; i++)
    {
        shreds[i] = new Shred(p_file_name + '_' + 'A' + i, p_block_size, truncate);
    }
}

bool ShredManager::encrypt(FileSpooler *fileSpooler, const char *key_file_name, const char *iv_file_name)
{

    AutoSeededRandomPool rnd;
    byte iv[AES::sizeof(iv)];
    rnd.GenerateBlock(iv, AES::sizeof(iv));
    ofstream fp;
    fp.open(iv_file_name.c_str(), ios::in | ios::out);
    if(fp.is_open()){
        fp.write((char *)&iv, 1);
        fp.close();
    }
    char *str;

    ofstream fp;
    fp.open(key_file_name.c_str(), ios::in | ios::out);
    if(fp.is_open()){
        fp.read(key_file_name.c_str(), 1);
        str = (char *)calloc(, sizeof(char));
        fp.write(str, key_file_name);
        fp.close();
    int count = 0;

    for(int i=0; b !=NULL; i++)
        shred[i%shred_count]->getNextBlock();
            b->encrypt(&str, &iv);
            *shreds[i] << &b;
        }
    }

    return true;
}
bool ShredManager::decrypt(FileSpooler *fileSpooler, const char *key_file_name, const char *iv_file_name)
{
        for(int i=0; b !=NULL; i++)
        shred[i%shred_count]->getNextBlock();
            b->decrypt(&key_file_name, &iv_file_name);
            fileSpooler->appendBlock(&b);            
        }
    }
    
    return false;
}
ShredManager::~ShredManager()
{
    for (int  i = 0; i < shred_count; i++)
        delete (shreds[i]);
    free(shreds);
}
