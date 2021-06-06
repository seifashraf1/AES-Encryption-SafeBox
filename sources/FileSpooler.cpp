#include <FileSpooler.h>

FileSpooler::FileSpooler(const char *p_file_name, uint16_t p_block_size, bool truncate)
{
    if (truncate)
        f.open(p_file_name, ios::in | ios::out | ios::trunc);
    else
        f.open(p_file_name, ios::in | ios::out);
    block_size = p_block_size;
}
Block *FileSpooler::getNextBlock()
{
    Block *b = new Block(block_size);
    b->load(f);               
    return *b;
     
}
void FileSpooler::appendBlock(Block *b)
{
    b->store(f);
}

FileSpooler::~FileSpooler()
{
    if (f.is_open())
        f.close();
}
