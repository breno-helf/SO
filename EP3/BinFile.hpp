// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef BIN_FILE_H
#define BIN_FILE_H

#include <iostream>
#include <fstream>
using namespace std;

struct node {
    char pid;
    int size;
    int pos;
    node *next;
};

class LinkedList {
private:
    
public:
    node *head;
    
    LinkedList();
    
    void print();
};

class BiFile {
private:
    char *aux;
    int size;
    fstream file;
    
public:
    BiFile(int s, char *st);
        
    void write(int pos, int s, char c);
        
    void read(int pos, int s, char *ret);
        
    void close();
    
    void copy(BiFile *origin, int pos, int s, int dest);
        
    void print();
};

#endif
