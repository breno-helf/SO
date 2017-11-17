// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
    void destroy(node *n);
        
public:
    node *head;
        
    LinkedList();
    
    void print();
    
    ~LinkedList();
    
};

#endif
