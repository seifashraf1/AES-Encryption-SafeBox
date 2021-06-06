#include <SafeBox.h>

SafeBox::SafeBox()
{
}
SafeBox::~SafeBox()
{
}
SafeBoxImport::SafeBoxImport()
{
}
void SafeBoxImport::process(char *input_file,
                            char *output_file,
                            char *working_dir,
                            char *key_file,
                            uint16_t block_size,
                            uint16_t shreds)
{
    printf("Import file\n");
    strcat(working_dir, "/");
    strcat(working_dir, input_file);
    ShredManager * sm = new ShredManager (input_file, block_size, shreds, &truncate);
    FileSpooler fileSpooler(input_file, block_size, &truncate);
    sm->encrypt(&fileSpooler, key_file, /Users/zaieda/Desktop/safebox/iv/iv.txt.rtfd);
    

}
SafeBox *SafeBoxImport::clone()
{
    return new SafeBoxImport();
}
SafeBoxImport::~SafeBoxImport()
{
}

SafeBoxExport::SafeBoxExport()
{
}
void SafeBoxExport::process(char *input_file,
                            char *output_file,
                            char *working_dir,
                            char *key_file,
                            uint16_t block_size,
                            uint16_t shreds)
{
    printf("Export file\n");
    strcat(working_dir, "/");
    strcat(working_dir, output_file);
    ShredManager * sm = new ShredManager (&output_file, block_size, shreds, truncate)
    FileSpooler fileSpooler(&output_file, block_size, truncate);
    sm->encrypt(fileSpooler, &key_file, &working_dir);
}
SafeBox *SafeBoxExport::clone()
{
    return new SafeBoxExport();
}
SafeBoxExport::~SafeBoxExport()
{
}
