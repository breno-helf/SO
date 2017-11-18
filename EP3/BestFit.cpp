// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "BestFit.hpp"
using namespace std;

        
BestFit::BestFit(BiFile &virMem, int total, int virt, int s, int p) {
    file = &virMem;
    this->total = total;
    this->virt = virt;
    this->s = s;
    pSize = p;
    l = new LinkedList(); 
    l->head = new node;
    l->head->pid = -1;
    l->head->pos = 0;
    l->head->size = total;
    l->head->IDsize = 0;
    l->head->next = NULL;
}
        
BestFit::~BestFit() {
    delete[] l;
}
        
bool BestFit::insert(char pid, int b) {
    int pidSize = (b/s);
    int size = (b/pSize);
    if (b%pSize) size++;
    if (b%s) pidSize++;
    size *= pSize;
    pidSize *= s;
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
    best->IDsize = pidSize;
    if (dif > 0) {
	node *n = new node;
	n->pid = -1;
	n->size = dif;
	n->IDsize = 0;
	n->next = best->next;
	n->pos = best->pos + size;
	best->next = n;
    }
    file->write(best->pos, best->IDsize, best->pid);
    file->write(best->pos + best->IDsize, best->size - best->IDsize, -1);
    return true;
}
        
void BestFit::remove(char pid) {
    node *curr;
    curr = l->head;
    while (curr->pid != pid) // <-- Atualmente esta linha da segfault 
	curr = curr->next;
    curr->pid = -1;
    file->write(curr->pos, curr->size, curr->pid);
    this->mergeWhite();
}
        
void BestFit::printll() {
    l->print();
}
        
void BestFit::compact(int *pageMap) {
    int *revMap = new int[virt/pSize];
    for (int i = 0; i < virt/pSize; i++)
        revMap[i] = i;
    node *curr;
    node *aux;
    curr = l->head;
    int cont = 0;
    while (curr != NULL) {
	    if (curr->pid != -1) {
	        cont += curr->size/pSize;    
	        curr = curr->next;
	    }
	    else {
	        if (curr->next != NULL) {
	    	    if (curr->next->pid == -1) {
	    	        aux = curr->next;
	    	        curr->size += aux->size;
	    	        curr->next = aux->next;
	    	        delete aux;
	    	    } else {
	    	        int auxS = (curr->size/pSize) + (curr->next->size/pSize);
	    	        int *auxMap = new int[auxS];
	    	        for (int i = 0; i < curr->next->size/pSize; i++)
	    	            auxMap[i] = pageMap[cont + (curr->size/pSize) + i];
	    	        for (int i = 0; i < curr->size/pSize; i++)
	    	            auxMap[i + curr->next->size/pSize] = pageMap[cont + i];
	    	        for (int i = 0; i <auxS; i++)
	    	            revMap[cont + i] = auxMap[i];
	    	        delete[] auxMap;
	    	        int a;
	    	        curr->pid = curr->next->pid;
	      	        a = curr->size;
	    	        curr->size = curr->next->size;
	    	        cont += curr->size/pSize;
	    	        file->write(curr->pos, curr->IDsize, curr->pid);
			file->write(curr->pos + curr->IDsize, curr->size - curr->IDsize, -1);
	    	        curr = curr->next;
	    	        file->write(curr->pos, curr->IDsize, curr->pid);
			file->write(curr->pos + curr->IDsize, curr->size - curr->IDsize, -1);
	    	        curr->pid = -1;
	    	        curr->size = a;
	    	    }
	       } else curr = curr->next;
	    }
    }
    for (int i = 0; i < virt/pSize; i++)
        pageMap[revMap[i]] = i;
}
   
int BestFit::translate(char pid, int p) {
    node *curr;
    curr = l->head;
    while (curr->pid != pid)
	curr = curr->next;
    return (curr->pos + p);
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
  //file.print();
  bf.remove(2);
  //bf.remove(1);
  bf.printll();
  bf.compact();
  cout << "---#---\n";
  bf.printll();
  bf.insert(4, 2);
  //file.print();
  //bf.printll();
  return 0;
  }
*/
