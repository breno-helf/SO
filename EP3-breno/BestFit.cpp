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
        
        LinkedList() {
            head = NULL;
        }
        
        void print() {
            node *curr;
            curr = head;
            while (curr != NULL) {
                cout << "pid = " << (short) curr->pid;
                cout << " size = " << curr->size;
                cout << " pos = " << curr->pos << "\n";
                curr = curr->next;
            }
        }
};

class BiFile {
    private:
        char *aux;
        int size;
        fstream file;
    
    public:
        BiFile(int s, char *st) {
            size = s;
            file.open(st, std::fstream::in | std::fstream::out | std::fstream::binary);
            aux = new char[1];
            aux[0] = -1;
            for (int j = 0; j < s; j++)
                file.write(aux, 1);
        }
        
        void write(int pos, int s, char c) {
            file.seekp(pos);
            aux[0] = c;
            for (int i = 0; i < s; i++)
                file.write(aux, 1);
        }
        
        void read(int pos, int s, char *ret) {
            file.seekg(pos);
            file.read(ret, s);
        }
        
        void close() {
            delete[] aux;
            file.close();
        }
    
        void copy(BiFile *origin, int pos, int s, int dest) {
            char *b = new char[s];
            origin->read(pos, s, b);
            file.seekp(dest);
            file.write(b, s);
        }
        
        void print() {
            char *buff = new char[size];
            this->read(0, size, buff);
            for (int i = 0; i < size; i++) {
                cout << (short) buff[i] << " ";
            }
            cout << "\n";
        }
};

class BestFit {
    private:
        BiFile *file;
        int total;
        int s;
        LinkedList *l;
    
        void mergeWhite() {
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
    
    
    public:
        BestFit(BiFile &realMem, int t, int q) {
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
        
        bool insert(char pid, int b) {
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
        
        void remove(char pid) {
            node *curr;
            curr = l->head;
            while (curr->pid != pid)
                curr = curr->next;
            curr->pid = -1;
            file->write(curr->pos, curr->size, curr->pid);
            this->mergeWhite();
        }
        
        void printll() {
            l->print();
        }
};

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
}