// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef PAGE_MEN_H
#define PAGE_MEN_H

#include <iostream>
#include <fstream>
#include <set>
#include "LinkedList.hpp"
#include "BinFile.hpp"
using namespace std;


class Fifo {
private:
    BiFile *fis;
    BiFile *vir;
    int vSize, pSize, tSize, s, pNum;
        
public:
    PageMen(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p);        
    ~PageMen();
    
    virtual void access(int pos);
    
    virtual void compact(int *pageMap);
};

#endif