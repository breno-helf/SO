// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef LRU4_H
#define LRU4_H

#include <iostream>
#include <fstream>
#include "LinkedList.hpp"
#include "BinFile.hpp"
#include "PageMen.hpp"
using namespace std;

/*struct page {
  char pid;
  int beg;
  };*/

class LRU4 : public PageMen {
private:
    pair<int, pair <int, unsigned long> > *list;
    unsigned long R;
        
public:
    LRU4(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p);
    
    ~LRU4();
    
    void access(int pos);
    
    void updateCount();
    
    void compact(int *pageMap);
};

#endif
