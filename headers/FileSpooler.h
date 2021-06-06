#ifndef FILESPOOLER_H
#define FILESPOOLER_H

#include <includes.h>
#include <defines.h>
#include <Block.h>

#include <iostream>
#include <fstream>

using namespace std;


class FileSpooler{
    private:
        uint16_t block_size;
        fstream f;
    public:
        FileSpooler(const char * p_file_name, uint16_t p_block_size, bool truncate =false);
        Block * getNextBlock();  
        void appendBlock (Block * b);      
        ~FileSpooler();
};


#endif