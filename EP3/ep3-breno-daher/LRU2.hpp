// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef LRU2_H
#define LRU2_H

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

class LRU2 : public PageMen {
private:
    int **matrix;
        
    int CompVal(int row1, int row2);
    
public:
    LRU2(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p);
    
    ~LRU2();
    
    int access(int pos);
    
    void compact(int *pageMap);
    
    void print();
    
    void remove(int begPos, int endPos);
};

#endif
