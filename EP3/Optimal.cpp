// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

// Incluir Optimal.o quando pronto
#include "Optimal.hpp"


Optimal::Optimal(BiFile &realMem, BiFile &virMem, int total,
		 int virt, int s, int p, trace * T) {
    fis = &realMem; vir = &virMem;
    tSize = total; vSize = virt; this->s = s; pSize = p;
    pNum = tSize/pSize;
    queue = vector<pair<int, int> >(pNum);
    vec = T->process_vec;

    int tam = vec.size();

    for (int i = 0; i < pNum; i++) {
        queue[i].first = -1;
        queue[i].second = i;
    }
    
    for (int i = 0; i < tam; i++) {
	int sz = vec[i].mem_acess.size();
	for (int j = 0; j < sz; j++) {
	    M[i]++;
	}
    }
}


Optimal::~Optimal() {
}
    
int Optimal::access(int pos) {
    int page = pos/pSize;
    if (MAP.find(page) == MAP.end()) {
	int tam = queue.size();
	int mn = 1000000;
	int id = -1;
	for (int i = 0; i < tam; i++) {
	    if (M[queue[i].second] < mn) {
		id = i;
		mn = min(M[queue[i].second], mn);
	    }
	}

	if (mn == -1) {
	    queue.push_back(make_pair(page, queue[id].second));
	    queue.erase(queue.begin() + id);
	} else {
	    MAP.erase(queue[id].first);
	    queue.push_back(make_pair(page, queue[id].second));
	    queue.erase(queue.begin() + id);
	}
	
	fis->copy(vir, page * pSize, pSize, queue[pNum - 1].second*pSize);
	MAP.insert(page);
	return 1;
    }
    M[pos]--;
    return 0;
}

void Optimal::compact(int *pageMAP) {
        for (int i = 0; i < pNum; i++)
        if (queue[i].first != -1) {
            MAP.erase(queue[i].first);
            queue[i].first = pageMAP[queue[i].first];
            MAP.insert(queue[i].first);
        }
}
    
void Optimal::remove(int begPos, int endPos) {
    if (begPos == -1 || endPos == -1) return;
    int begPage = begPos/pSize, endPage = endPos/pSize;
    for (int i = 0; i < pNum; i++)
        if (queue[i].first >= begPage && queue[i].first <= endPage) {
            fis->write(queue[i].second*pSize, pSize, -1);
            queue[i].first = -1;
            if (MAP.find(queue[i].first) != MAP.end())
		MAP.erase(queue[i].first);
        }
}
