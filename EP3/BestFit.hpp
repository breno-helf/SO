// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef BEST_FIT_H
#define BEST_FIT_H

#include <iostream>
#include <fstream>
#include "LinkedList.hpp"
#include "BinFile.hpp"
#include "MemoryMen.hpp"
using namespace std;

class BestFit : MemoryMen {
public:
    BestFit(BiFile &realMem, int t, int v, int q, int p);        

    ~BestFit();
    
    bool insert(char pid, int b);
    
    void remove(char pid);
    
    void printll();
    
    void compact(int *pageMap);
    
    int translate(char pid, int p);
    
};

#endif
