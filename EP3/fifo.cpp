// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "fifo.hpp"
using namespace std;

Fifo::Fifo(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p) {
    fis = &realMem; vir = &virMem;
    tSize = total; vSize = virt; this->s = s; pSize = p;
    pNum = tSize/pSize;
    queue = vector<pair<int, int> >(pNum);
    for (int i = 0; i < pNum; i++) {
        queue[i].first = -1;
        queue[i].second = i;
    }
}
        
Fifo::~Fifo() {
}
        
int Fifo::access(int pos) {
    int page = pos/pSize, pointer;
    if (map.find(page) == map.end()) {
	    for (pointer = 0; pointer < pNum && queue[pointer].first != -1; pointer++);
	    if (pointer == pNum) {
	        map.erase(queue[0].first);
	        queue.push_back(make_pair(page, queue[0].second));
	        queue.erase(queue.begin());
	    }
	    else {
	        queue.push_back(make_pair(page, queue[pointer].second));
	        queue.erase(queue.begin() + pointer);
	    }
	    fis->copy(vir, page*pSize, pSize, queue[pNum - 1].second*pSize);
	    map.insert(page);
	    return 1;
	}
	return 0;
}

void Fifo::compact(int *pageMap) {
    for (int i = 0; i < pNum; i++)
        if (queue[i].first != -1) {
            map.erase(queue[i].first);
            queue[i].first = pageMap[queue[i].first];
            map.insert(queue[i].first);
        }
}

void Fifo::print() {
    for (unsigned int i = 0; i < queue.size(); i++)
        cout << queue[i].first << "/" << queue[i].second << " ";
    cout << "\n";
}

void Fifo::remove(int begPos, int endPos) {
    if (begPos == -1 || endPos == -1) return;
    int begPage = begPos/pSize, endPage = endPos/pSize;
    for (int i = 0; i < pNum; i++)
        if (queue[i].first >= begPage && queue[i].first <= endPage) {
            fis->write(queue[i].second*pSize, pSize, -1);
            queue[i].first = -1;
            map.erase(queue[i].first);
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
