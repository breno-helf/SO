// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef OPTIMAL_H
#define OPTIMAL_H

#include "PageMen.hpp"
#include "trace.hpp"
#include <map>
#include <set>
#include <vector>
using namespace std;


class Optimal : public PageMen {
private:
    vector<pair<int, int> > queue;
    set <int> MAP;
    vector<process> vec;
    map<int, int> M;
    
public:
    Optimal(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p, trace * T);        
    ~Optimal();
    
    int access(int pos);
    
    void compact(int *pageMap);

    void remove(int begPos, int endPos);

};

#endif
