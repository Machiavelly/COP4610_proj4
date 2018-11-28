#ifndef BACKINGSTORE_H
#define BACKINGSTORE_H

#include "addrspace.h"
#include "filesys.h"
#include "bitmap.h"

class BackingStore {
public:
    BackingStore(int pid, int numPages);
    ~BackingStore();
    void MovePageToBackingStore(TranslationEntry* entry); //return false on failure to read
    int TranslateToOffset(TranslationEntry* entry);
    void MovePageToMemory(TranslationEntry* entry); //return false on failure to write
    
private:
    OpenFile* backingStore;
    char* fileName;
    BitMap* usedPages;
};

#endif /* BACKINGSTORE_H */

