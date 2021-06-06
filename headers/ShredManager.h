#ifndef SHREDMANAGER_H
#define SHREDMANAGER_H

#include <includes.h>
#include <defines.h>
#include <FileSpooler.h>
#include <Shred.h>

class ShredManager {
    private:
        Shred ** shreds;
        uint16_t shred_count;
    public:
        ShredManager(char * p_file_name, uint16_t p_block_size, uint16_t p_shred_count,bool truncate = false);
        bool encrypt (FileSpooler * fileSpooler, const char * key_file_name, const char * iv_file_name);
        bool decrypt (FileSpooler * fileSpooler, const char * key_file_name, const char * iv_file_name);
        ~ShredManager();
};


#endif