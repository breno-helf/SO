// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "fifo.hpp"
using namespace std;

/*struct page {
  char pid;
  int beg;
  };*/

Fifo::Fifo(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p) {
    fis = &realMem; vir = &virMem;
    tSize = total; vSize = virt; this->s = s; pSize = p;
    pNum = vSize/pSize;
    queue = new int[pNum];
    for (int i = 0; i < pNum; i++) {
	queue[i] = -1;
    }
    pointer = 0;
}
        
Fifo::~Fifo() {
    delete queue;
}
        
void Fifo::access(int pos) {
    int page = pos/pSize;
    if (map.find(page) == map.end()) {
	if (queue[pointer] != -1)
	    map.erase(queue[pointer]);
	queue[pointer] = page;
	vir->copy(fis, page*pSize, pSize, pointer*pSize);
	pointer = (pointer + 1) %pNum;
	map.insert(page);
    }
}

/*
  int main() {
  char *name = new char[2];
  name[0] = 't'; name[1] = '1';
  BiFile vir(16, name);
  name[1] = '2';
  BiFile real(64, name);
  BestFit bf(real, 64, 2);
  Fifo f(real, vir, 64, 16, 2, 4);
  vir.print();
  bf.insert(1, 10);
  bf.insert(2, 10);
  bf.insert(3, 10);
  bf.insert(4, 10);
  bf.insert(5, 10);
  bf.insert(6, 10);
  f.access(0);
  f.access(4);
  f.access(8);
  f.access(12);
  f.access(16);
  f.access(20);
  vir.print();
  return 0;
  }
*/
