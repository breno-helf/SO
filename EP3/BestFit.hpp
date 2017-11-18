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

class BestFit : public MemoryMen {
public:
    BestFit(BiFile &virMem, int total, int virt, int s, int p);

    ~BestFit();
    
    bool insert(char pid, int b);
    
    void remove(char pid);
    
    void printll();
    
    void compact(int *pageMap);
    
    int translate(char pid, int p);
    
    int size(char pid);
};

#endif
