// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include "trace.hpp"
using namespace std;

vector<string> stringToVec(string s) {
    vector<string> ret;
    string r = "";
    for (int i = 0; i < (int)s.size(); i++) {
	if (!isspace(s[i])) r += s[i];
	else {
	    if (r != "") {
		ret.push_back(r);
		r = "";
	    }
	}
    }

    if (r != "") ret.push_back(r);
    
    return ret;
}

trace * load_file(string file_name) {
    ifstream trace_file (file_name.c_str());
    string line;
    vector<string> objs;
    trace * ret = (trace *) malloc(sizeof(trace));
    getline(trace_file, line);
    objs = stringToVec(line);

    assert((int)objs.size() == 4);
    
    ret->total = atoi(objs[0].c_str());
    ret->virt  = atoi(objs[1].c_str());
    ret->s     = atoi(objs[2].c_str());
    ret->p     = atoi(objs[3].c_str());
    
    while (getline(trace_file, line)) {
	objs = stringToVec(line);
	if ((int)objs.size() == 2) {
	    if (objs[1] == "COMPACTAR") {
		action compact = action(4, atof(objs[1].c_str()), -1, -1);
		ret->action_queue.push(compact);
	    }
	} else {
	    process p;
	    int PID = ret->process_vec.size();
	    p.t0 = atof(objs[0].c_str());
	    p.tf = atof(objs[1].c_str());
	    p.b  = atoi(objs[2].c_str());
	    p.name = objs[3];
	    action initialize = action(2, p.t0, PID, -1);
	    action finalize   = action(3, p.tf, PID, -1);
	    
	    for (int i = 4; i < (int)objs.size(); i += 2) {
		acess A;
		int AID = p.mem_acess.size();
		
		A = acess(atoi(objs[i].c_str()), atof(objs[i + 1].c_str()));
		ret->action_queue.push(action(1, A.t, PID, AID)); 
		p.mem_acess.push_back(A);
	    }
	    ret->process_vec.push_back(p);
	    ret->action_queue.push(initialize);
	    ret->action_queue.push(finalize);
	}	
    }
    trace_file.close();
    
    return ret;
}

void simulate(trace * T, int mem_type, int pag_type) {
    // Cria as classes dos tipos que você quer


    for (int cur_time = 0; !(T->action_queue.empty(); cur_time++) {
	    // Tempo atual eh cur_time 
	    while(!(T->action_queue.empty()) && T->action_queue.top() == cur_time) {
		action A = T->action_queue.top();
		T->action_queue.pop();
		
		if (A.type == 1) {
		    // Acessa a memória na paginação
		} else if (A.type == 2) {
		    // Inicializa um processo
		} else if (A.type == 3) {
		    // Finaliza um processo
		} else if (A.type == 4) {
		    // Compacta
		} else {
		    cerr << "Tipo de acao nao valido " << A.type << "\n";
		    exit(-1);
		}	
	    }	    
	}
}

int main(int argc, char * argv[]) {
    trace * cur_trace;
    int mem_type = -1;
    int pag_type = -1;
    while (true) {
	string s;
	cin >> s;
	if (s == "carrega") {
	    string file_name;
	    cin >> file_name;
	    cur_trace = load_file(file_name);	    
	} else if (s == "espaco") {
	    // Change de algortihm that manages memory
	    cin >> mem_type;
	} else if (s == "substitui") {
	    // Change de algorithm that manages pages
	    cin >> pag_type;
	} else if (s == "executa") {
	    if (mem_type == -1 || pag_type == -1)
		cerr << "Voce deve informar o tipo de simulador a ser executado\n";
	    else {
		// Executa o algoritimo
		simulate(cur_trace, mem_type, pag_type);
	    }
	} else {
	    break;
	}
	fflush(stdout);
    }
}
