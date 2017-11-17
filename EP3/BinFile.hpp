// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <iostream>
#include <fstream>
#include "LinkedList.hpp"
using namespace std;

class BiFile {
private:
    char *aux;
    int size;
    fstream file;
    
public:
    BiFile(int s, char *st);        

    ~BiFile();
        
    void write(int pos, int s, char c);
        
    void read(int pos, int s, char *ret);
    
    void copy(BiFile *origin, int pos, int s, int dest);
    
    void print();
};

#endif
