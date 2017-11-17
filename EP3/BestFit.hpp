// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef BEST_FIT_H
#define BEST_FIT_H

#include <iostream>
#include <fstream>
#include "LinkedList.hpp"
#include "BinFile.hpp"
using namespace std;

class BestFit {
private:
    BiFile *file;
    int total;
    int s;
    LinkedList *l;
    
    void mergeWhite();    
    
public:
    BestFit(BiFile &realMem, int t, int q);        

    ~BestFit();
    
    bool insert(char pid, int b);
    
    void remove(char pid);
    
    void printll();
    
    void compact();
    
    int translate(char pid, int p);
    
};

#endif
