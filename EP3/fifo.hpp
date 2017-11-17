// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef FIFO_H
#define FIFO_H

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
    int vSize, pSize, tSize, s, pNum, pointer;
    int *queue;
    set <int> map;
        
public:
    Fifo(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p);        
    ~Fifo();
    
    void access(int pos);
    
    void compact(int *pageMap);
};

#endif
