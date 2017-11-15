// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "BestFit.hpp"
using namespace std;

void BestFit::mergeWhite() {
    node *curr;
    curr = l->head;
    while (curr->next != NULL) {
	if (curr->pid == -1 && curr->next->pid == -1) {
	    node *t;
	    t = curr->next;
	    curr->size += curr->next->size;
	    curr->next = curr->next->next;
	    delete t;
	}
	else curr = curr->next;
    }
}
    
    
BestFit::BestFit(BiFile &realMem, int t, int q) {
    file = &realMem;
    total = t;
    s = q;
    l = new LinkedList(); 
    l->head = new node;
    l->head->pid = -1;
    l->head->pos = 0;
    l->head->size = t;
    l->head->next = NULL;
}
        
bool BestFit::insert(char pid, int b) {
    int size = (b/s);
    if (b%s) size++;
    size *= s;
    node *best;
    node *curr;
    curr = best = l->head;
    while (curr != NULL) {
	if (curr->pid == -1) {
	    if (best->pid != -1) {
		best = curr;
	    }
	    else {
		if (curr->size >= s && curr->size < best->size) {
		    best = curr;
		}
	    }
	}
	curr = curr->next;
    }
    if (best->size < size) return false;
    int dif = best->size - size;
    best->pid = pid;
    best->size = size;
    if (dif > 0) {
	node *n = new node;
	n->pid = -1;
	n->size = dif;
	n->next = best->next;
	n->pos = best->pos + size;
	best->next = n;
    }
    file->write(best->pos, best->size, best->pid);
    return true;
}
        
void BestFit::remove(char pid) {
    node *curr;
    curr = l->head;
    while (curr->pid != pid)
	curr = curr->next;
    curr->pid = -1;
    file->write(curr->pos, curr->size, curr->pid);
    this->mergeWhite();
}
        
void BestFit::printll() {
    l->print();
}

/*
  int main() {
  char *name = new char[2];
  name[0] = 't'; name[1] = '3';
  BiFile file(16, name);
  BestFit bf(file, 16, 2);
  bf.insert(1, 2);
  bf.insert(2, 2);
  bf.insert(3, 3);
  file.print();
  bf.printll();
  bf.remove(2);
  bf.remove(1);
  bf.insert(4, 2);
  file.print();
  bf.printll();
  return 0;
  }*/
