// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "BinFile.hpp"
using namespace std;

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

BiFile::BiFile(int s, char *st) {
    size = s;
    file.open(st, fstream::in | fstream::out | fstream::binary);
    aux = new char[1];
    aux[0] = -1;
    for (int j = 0; j < s; j++)
	file.write(aux, 1);
}

void BiFile::write(int pos, int s, char c) {
    file.seekp(pos);
    aux[0] = c;
    for (int i = 0; i < s; i++)
	file.write(aux, 1);
}
        
void BiFile::read(int pos, int s, char *ret) {
    file.seekg(pos);
    file.read(ret, s);
}
        
void BiFile::close() {
    delete[] aux;
    file.close();
}
    
void BiFile::copy(BiFile *origin, int pos, int s, int dest) {
    char *b = new char[s];
    origin->read(pos, s, b);
    file.seekp(dest);
    file.write(b, s);
}
        
void BiFile::print() {
    char *buff = new char[size];
    this->read(0, size, buff);
    for (int i = 0; i < size; i++) {
	cout << (short) buff[i] << " ";
    }
    cout << "\n";
}
