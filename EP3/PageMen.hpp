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

class PageMen {
protected:
    BiFile *fis;
    BiFile *vir;
    int vSize, pSize, tSize, s, pNum;
        
public:
    PageMen();        
    ~PageMen();
    
    virtual void access(int pos);
    
    virtual void compact(int *pageMap);
    
    virtual void print();
    
    virtual void remove(int begPos, int endPos);
};

#endif
