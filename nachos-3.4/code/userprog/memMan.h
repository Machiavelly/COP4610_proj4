#include "machine.h"
#define NUM_PAGES 32

class memMan {
public:

    memMan();
    int allocate();
    void deallocate(int pageNum);
    int getPages();
    //page swapping
    int findVictimPage();

private:
    bool mem[NUM_PAGES];
    int numPages;
    int pageIndex;
    //page swapping
    int orderAllocated[NUM_PAGES];
    int orderAllocatedCounter; //circular counter from 0 to [NUM_PAGES - 1]
    int nextToEvict;

};
