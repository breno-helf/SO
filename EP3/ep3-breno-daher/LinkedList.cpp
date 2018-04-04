// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "LinkedList.hpp"
using namespace std;

void LinkedList::destroy(node * n) {
    if (n->next != NULL) destroy(n->next);
    delete[] n;
}

LinkedList::LinkedList() {
    head = NULL;
}
        
void LinkedList::print() {
    node *curr;
    curr = head;
    while (curr != NULL) {
	cerr << "pid = " << (short) curr->pid;
	cerr << " size = " << curr->size;
	cerr << " pos = " << curr->pos << "\n";
	curr = curr->next;
    }
}

LinkedList::~LinkedList() {
    destroy(head);
}
