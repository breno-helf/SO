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
	cout << "pid = " << (short) curr->pid;
	cout << " size = " << curr->size;
	cout << " pos = " << curr->pos << "\n";
	curr = curr->next;
    }
}

LinkedList::~LinkedList() {
    destroy(head);
}
