// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include "LinkedList.hpp"
#include "BinFile.hpp"
#include "PageMen.hpp"
using namespace std;


class Fifo : public PageMen {
private:
    vector<pair<int, int> > queue;
    set <int> map;
        
public:
    Fifo(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p);        
    ~Fifo();
    
    int access(int pos);
    
    void compact(int *pageMap);
    
    void print();
    
    void remove(int begPos, int endPos);
};

#endif
