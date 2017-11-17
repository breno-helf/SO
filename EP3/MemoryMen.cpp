// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#ifndef MEMORY_MEN_H
#define MEMORY_MEN_H

#include "MemoryMen.hpp"
using namespace std;

void MemoryMen::mergeWhite() {
    node *curr;
    curr = l->head;
    while (curr->next != NULL) {
	if (curr->pid == -1 && curr->next->pid == -1) {
	    node *t;
	    t = curr->next;
	    curr->size += curr->next->size;
	    curr->next = curr->next->next;
	    delete[] t;
	}
	else curr = curr->next;
    }
}

MemoryMen::MemoryMen(BiFile &realMem, int t, int v, int q, int p) {
    return;
}

MemoryMen::~MemoryMen() {
    return;
}
    
virtual bool MemoryMen::insert(char pid, int b) {
    return false;
}

virtual void MemoryMen::remove(char pid) {
    return;
}

virtual void MemoryMen::printll() {
    return;
}

virtual void MemoryMen::compact(int *pageMap) {
    return;
}

virtual int MemoryMen::translate(char pid, int p) {
    return 0;
}

#endif
