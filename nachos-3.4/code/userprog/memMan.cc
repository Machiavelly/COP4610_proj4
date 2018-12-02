#include "memMan.h"

memMan::memMan() {
    int i;
    for (i = 0; i < NUM_PAGES; i++) {
        mem[i] = false;
        orderAllocated[i] = -1;
    }
    orderAllocatedCounter = 0;
    nextToEvict = 0; //requires the first page to be allocated to always be at index 0
}

int memMan::allocate() {
    int i;
    for (i = 0; i < NUM_PAGES; i++) {
        if (mem[i] == false) {
            mem[i] = true;
            numPages++;
            pageIndex++;
            
            //update the circular counter 
            orderAllocatedCounter++;
            orderAllocatedCounter %= NUM_PAGES;
            
            orderAllocated[i] = orderAllocatedCounter;
            return i;
        }
    }
    return -1;
}

void memMan::deallocate(int pageNum) {
    mem[pageNum] = false;
    numPages--;
    pageIndex--;
    nextToEvict++;
}

int memMan::getPages() {
    DEBUG('d', "\n\tVariables in mans_man: NumPhysPages:%d, numPages:%d\n", NumPhysPages, numPages);
    return (NumPhysPages - numPages);
}

int memMan::findVictimPage() {
    int i;
    for (i = 0; i < NUM_PAGES; i++) {
        if (orderAllocated[i] == nextToEvict) {
            ASSERT(mem[i] == true); //make sure the next page to evict has been allocated previously
            return i;
        }
    }
    return -1;
}