// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef BEST_FIT_H
#define BEST_FIT_H

#include <iostream>
#include <fstream>
#include "LinkedList.hpp"
#include "BinFile.hpp"
using namespace std;

class MemoryMen {
private:
    BiFile *file;
    int total, virt;
    int s, pSize;
    LinkedList *l;
    
    void mergeWhite();
    
public:
    MemoryMen(BiFile &realMem, int t, int v, int q, int p);        

    ~MemoryMen();
    
    virtual bool insert(char pid, int b);
    
    virtual void remove(char pid);
    
    virtual void printll();
    
    virtual void compact(int *pageMap);
    
    virtual int translate(char pid, int p);
    
};

#endif