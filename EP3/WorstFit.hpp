// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef WORST_FIT_H
#define WORST_FIT_H

#include <iostream>
#include <fstream>
#include "MemoryMen.hpp"
using namespace std;

class WorstFit : public MemoryMen {
public:
    WorstFit(BiFile &virMem, int total, int virt, int s, int p);

    ~WorstFit();
    
    bool insert(char pid, int b);
    
    void remove(char pid);
    
    void printll();
    
    void compact(int *pageMap);
    
    int translate(char pid, int p);
    
};

#endif
