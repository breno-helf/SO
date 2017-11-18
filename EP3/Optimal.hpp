// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef OPTIMAL_H
#define OPTIMAL_H

#include "PageMen.hpp"
using namespace std;


class Optimal : public PageMen {
private:
    int pointer;
    int *queue;
    set <int> map;
        
public:
    Optimal(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p);        
    ~Optimal();
    
    void access(int pos);
    
    void compact(int *pageMap);
};

#endif
