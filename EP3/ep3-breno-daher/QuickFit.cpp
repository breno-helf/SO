// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "QuickFit.hpp"

void QuickFit::UpdateQuick() {
    node * curr;

    HeadB = HeadA = NULL;

    LList * Acur = NULL;
    LList * Bcur = NULL;
    
    curr = l->head;
    while (curr != NULL) {
	if (curr->size >= sizeA && curr->pid == -1) {

	    if (Acur == NULL) {
		HeadA = new LList;
		HeadA->me = curr;
		Acur = HeadA;
	    } else {
		Acur->next = new LList;
		Acur->next->me = curr;
		Acur = Acur->next;
	    }
	}

	if (curr->size >= sizeB && curr->pid == -1) {

	    if (Bcur == NULL) {
		HeadB = new LList;
		HeadB->me = curr;
		Bcur = HeadB;
	    } else {
		Bcur->next = new LList;
		Bcur->next->me = curr;
		Bcur = Bcur->next;
	    }
	}
	
	curr = curr->next;
    }
}


QuickFit::QuickFit(BiFile &virMem, int total, int virt, int s, int p,
	 trace * T) {
    file = &virMem;
    this->total = total;
    this->virt = virt;
    this->s = s;
    pSize = p;
    if (p < s) pSize = s;
    l = new LinkedList(); 
    l->head = new node;
    l->head->pid = -1;
    l->head->pos = 0;
    l->head->size = virt;
    l->head->IDsize = 0;
    l->head->next = NULL;
    
    map<int, int> M, N;
    int tam = T->process_vec.size();

    for (int i = 0; i < tam; i++) {
	M[T->process_vec[i].b]++;
    }

    for (map<int,int>::iterator it = M.begin(); it != M.end(); ++it) {
	N[it->second] = it->first;
    }

    map<int,int>::iterator it;
    it = N.end();
    
    --it;
    sizeA = it->second;

    if (it != N.begin()) {
	--it;
	sizeB = it->second;
    } else {
	sizeB = -1;
    }

    this->UpdateQuick();
}

QuickFit::~QuickFit() {
    delete[] l;
}

bool QuickFit::insert(char pid, int b) {
    if (b == sizeA) {
	if (HeadA == NULL) return false;
	int pidSize = (b/s);
	int size = (b/pSize);
	if (b%s) pidSize++;
	if (b%pSize) size++;
	pidSize *= s;
	size *= pSize;
	
	node * best;
	best = HeadA->me;

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
	this->UpdateQuick();
	return true;	
    } else if (b == sizeB) {
	if (HeadB == NULL) return false;

	int pidSize = (b/s);
	int size = (b/pSize);
	if (b%s) pidSize++;
	if (b%pSize) size++;
	pidSize *= s;
	size *= pSize;
	
	node * best;
	best = HeadB->me;
	
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
	this->UpdateQuick();
	return true;
    } else {
	int pidSize = (b/s);
	int size = (b/pSize);
	if (b%s) pidSize++;
	if (b%pSize) size++;
	pidSize *= s;
	size *= pSize;
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
	this->UpdateQuick();
	return true;
    }
}

void QuickFit::remove(char pid) {
    node *curr;
    curr = l->head;
    while (curr != NULL && curr->pid != pid)
        curr = curr->next;
    if (curr == NULL) {
        cout << "nao achou o processo de pid " << (short) pid << "\n";
        return;
    }
    curr->pid = -1;
    file->write(curr->pos, curr->size, curr->pid);
    this->mergeWhite();
    this->UpdateQuick();
}

void QuickFit::printll() {
    l->print();
}

void QuickFit::compact(int *pageMap) {
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
                        auxMap[i] = revMap[cont + (curr->size/pSize) + i];
                    for (int i = 0; i < curr->size/pSize; i++)
                        auxMap[i + curr->next->size/pSize] = revMap[cont + i];
                    for (int i = 0; i <auxS; i++)
                        revMap[cont + i] = auxMap[i];
                    delete[] auxMap;
                    int a;
                    curr->pid = curr->next->pid;
                    a = curr->size;
                    curr->size = curr->next->size;
                    curr->IDsize = curr->next->IDsize;
                    cont += curr->size/pSize;
                    file->write(curr->pos, curr->IDsize, curr->pid);
                    file->write(curr->pos + curr->IDsize, curr->size - curr->IDsize, -1);
                    curr->next->pos = curr->pos + curr->size;
                    curr = curr->next;
                    curr->pid = -1;
                    curr->size = a;
                    curr->IDsize = 0;
                    file->write(curr->pos, curr->size, -1);
                }
            } else curr = curr->next;
        }
    }
    for (int i = 0; i < virt/pSize; i++)
        pageMap[revMap[i]] = i;
}

int QuickFit::translate(char pid, int p) {
    node *curr;
    curr = l->head;
    while (curr != NULL && curr->pid != pid)
        curr = curr->next;
    if (curr == NULL) return -1;
    return (curr->pos + p);
}


int QuickFit::size(char pid) {
    node *curr;
    curr = l->head;
    while (curr != NULL && curr->pid != pid)
        curr = curr->next;
    if (curr == NULL) return -1;
    return (curr->size);
}
