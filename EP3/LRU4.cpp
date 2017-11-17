// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "LRU4.hpp"
using namespace std;

/*struct page {
  char pid;
  int beg;
  };*/

LRU4::LRU4(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p) {
    fis = &realMem; vir = &virMem;
    tSize = total; vSize = virt; this->s = s; pSize = p;
    pNum = vSize/pSize;
    list = new pair<int, pair<int, unsigned long> >[pNum];
    for (int i = 0; i < pNum; i++) {
	list[i].first = -1;
	list[i].second.first = 0;
	list[i].second.second = 0;
    }
    R = 1;
    if ((R << 1) > 0) R = R << 1;
}
        
LRU4::~LRU4() {
    delete[] list;
}
        
void LRU4::access(int pos) {
    int page = pos/pSize;
    int p = 0;
    for (int i = 0; i < pNum; i++) {
	if (list[i].first == page) {
	    list[i].second.first = 1;
	    return;
	}
	else if (list[i].first == -1) p = i;
	else {
	    if (list[p].first != -1) {
		if (list[p].second.second > list[i].second.second)
		    p = i;
	    }
	}
    }
    list[p].first = page;
    vir->copy(fis, page*pSize, pSize, p*pSize);
    list[p].second.first = 1;
}
        
void LRU4::updateCount() {
    for (int i = 0; i < pNum; i++) {
	list[i].second.second = list[i].second.second >> 1;
	if (list[i].second.first == 1)
	    list[i].second.second += R;
	list[i].second.first = 0;
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
  LRU4 f(real, vir, 64, 16, 2, 4);
  vir.print();
  bf.insert(1, 10);
  bf.insert(2, 10);
  bf.insert(48, 10);
  bf.insert(4, 10);
  bf.insert(107, 10);
  bf.insert(6, 10);
  f.access(0);
  f.access(8);
  f.updateCount();
  f.access(16);
  f.updateCount();
  f.access(24);
  f.updateCount();
  f.access(32);
  f.access(40);
  f.updateCount();
  vir.print();
  return 0;
  }
*/
