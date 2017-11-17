// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "LRU2.hpp"
using namespace std;

/*struct page {
  char pid;
  int beg;
  };*/

        
int LRU2::CompVal(int row1, int row2) {
    for (int i = 1; i <= pNum; i++) {
	if (matrix[row1][i] > matrix[row2][i]) return 1;
	if (matrix[row1][i] > matrix[row2][i]) return -1;
    }
    return 0;
}
        
LRU2::LRU2(BiFile &realMem, BiFile &virMem, int total, int virt, int s, int p) {
    fis = &realMem; vir = &virMem;
    tSize = total; vSize = virt; this->s = s; pSize = p;
    pNum = vSize/pSize;
    matrix = new int*[pNum];
    for (int i = 0; i < pNum; i++)
	matrix[i] = new int[pNum + 1];
    for (int i = 0; i < pNum; i++)
	for (int j = 0; j <= pNum; j++) {
	    if (j == 0) matrix[i][j] = -1;
	    else matrix[i][j] = 0;
	}
}
        
LRU2::~LRU2() {
    for (int i = 0; i < pNum; i++)
	delete[] matrix[i];
    delete[] matrix;
}
        
void LRU2::access(int pos) {
    int page = pos/pSize;
    int p = 0;
    for (int i = 0; i < pNum; i++) {
	if (matrix[i][0] == page) {
	    for (int j = 0; j < pNum; j++) {
		matrix[j][i] = 0;
		matrix[i][j + 1] = 1;
	    }
	    return;
	}
	else if (matrix[i][0] == -1) p = i;
	else {
	    if (matrix[p][0] != -1) {
		if (CompVal(p, i) == 1) p = i;
	    }
	}
    }
    matrix[p][0] = page;
    for (int j = 0; j < pNum; j++) {
	matrix[j][p] = 0;
	matrix[p][j + 1] = 1;
    }
    vir->copy(fis, page*pSize, pSize, p*pSize);
}

/*
  int main() {
  char *name = new char[2];
  name[0] = 't'; name[1] = '1';
  BiFile vir(16, name);
  name[1] = '2';
  BiFile real(64, name);
  BestFit bf(real, 64, 2);
  LRU2 f(real, vir, 64, 16, 2, 4);
  vir.print();
  bf.insert(1, 10);
  bf.insert(2, 10);
  bf.insert(48, 10);
  bf.insert(4, 10);
  bf.insert(107, 10);
  bf.insert(6, 10);
  f.access(0);
  f.access(8);
  f.access(16);
  f.access(24);
  f.access(32);
  f.access(40);
  vir.print();
  return 0;
  }
*/
