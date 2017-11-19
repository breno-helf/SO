// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef QUICK_FIT_H
#define QUICK_FIT_H

#include <iostream>
#include <fstream>
#include <map>
#include "MemoryMen.hpp"
#include "trace.hpp"
using namespace std;

struct LList {
    node * me;
    struct LList * next;
};

class QuickFit : public MemoryMen {
private:
    LList * HeadA;
    LList * HeadB;
    int sizeA;
    int sizeB;

    void UpdateQuick();
    
public:
    QuickFit(BiFile &virMem, int total, int virt, int s, int p, trace * T);

    ~QuickFit();
    
    bool insert(char pid, int b);
    
    void remove(char pid);
    
    void printll();
    
    void compact(int *pageMap);
    
    int translate(char pid, int p);

    int size(char pid);
};

#endif
