// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

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

MemoryMen::MemoryMen() {
    return;
}

MemoryMen::~MemoryMen() {
    return;
}
    
bool MemoryMen::insert(char pid, int b) {
    return false;
}

void MemoryMen::remove(char pid) {
    return;
}

void MemoryMen::printll() {
    return;
}

void MemoryMen::compact(int *pageMap) {
    return;
}

int MemoryMen::translate(char pid, int p) {
    return 0;
}
