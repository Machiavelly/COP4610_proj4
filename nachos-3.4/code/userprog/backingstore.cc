#include "backingstore.h"
#include "system.h"

BackingStore::BackingStore(int pid, int numPages) {
    fileName = new char[11];
    sprintf(fileName, "bs_%d", pid);
    DEBUG('d',"BackingStore creating file...\n");
    fileSystem->Create(fileName, numPages * PageSize);
    DEBUG('d',"BackingStore created file. BackingStore opening file...\n");
    backingStore = fileSystem->Open(fileName);
    DEBUG('d',"BackingStore opened.\n");
    usedPages = new BitMap(numPages);
}

BackingStore::~BackingStore() {
    fileSystem->Remove(fileName);
    delete backingStore;
    backingStore = 0;
    delete usedPages;
    usedPages = 0;
}

void BackingStore::MovePageToBackingStore(TranslationEntry* entry) {
    int offset = TranslateToOffset(entry);
    int physAddr = entry->physicalPage * PageSize;
    
    backingStore->WriteAt(
            &machine->mainMemory[physAddr],
            PageSize,
            offset
    );
    entry->isInMemory = false;
    entry->bsOffset = offset;
}

int BackingStore::TranslateToOffset(TranslationEntry* entry) {
    int openPage = usedPages->Find();
    ASSERT(openPage != -1); // no open page could be found in the backing store!
    int offset = openPage * PageSize;
    return offset;
}

void BackingStore::MovePageToMemory(TranslationEntry* entry) {
    int bsPage = entry->bsOffset / PageSize;
    ASSERT(usedPages->Test(bsPage));
    int physAddr = entry->physicalPage * PageSize;
    int offset = entry->virtualPage * PageSize;

    backingStore->ReadAt(&machine->mainMemory[physAddr], 
            PageSize, 
            offset);
}
