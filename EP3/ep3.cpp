// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include "trace.hpp"
#include "BestFit.hpp"
#include "MemoryMen.hpp"
#include "PageMen.hpp"
#include "LRU2.hpp"
#include "LRU4.hpp"
#include "fifo.hpp"
#include "LinkedList.hpp"
#include "BinFile.hpp"
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

void simulate(trace * T, int mem_type, int pag_type, int start_time, int end_time) {
    // Cria as classes dos tipos que você quer

    char * virt_dir = (char *) malloc(sizeof(char) * 10);
    char * real_dir = (char *) malloc(sizeof(char) * 10);
    
    strcpy(virt_dir, "/tmp/ep3.vir");
    strcpy(real_dir, "/tmp/ep3.mem");


    MemoryMen * M;
    BiFile * VirtualMem = new BiFile(T->virt, virt_dir);
    PageMen * P;
    BiFile * RealMem = new BiFile(T->total, real_dir);


    if (mem_type == 1) {
	M = new BestFit(*VirtualMem, T->total, T->virt, T->s, T->p);
    } else if (mem_type == 2) {
	// Worst Fit
    } else {
	// Quick Fit
    }

    if (pag_type == 1) {
	// Optimal
    } else if (pag_type == 2) {
	P = new Fifo(*RealMem, *VirtualMem, T->total, T->virt, T->s, T->p);
    } else if (pag_type == 3) {
	P = new LRU2(*RealMem, *VirtualMem, T->total, T->virt, T->s, T->p);
    } else {
	P = new LRU4(*RealMem, *VirtualMem, T->total, T->virt, T->s, T->p);
    }

    cerr << "Cheguei aqui " << endl;
    
    for (int cur_time = 0; !(T->action_queue.empty()); cur_time++) {
	// Tempo atual eh cur_time

	if (cur_time == start_time) {
	    // ativa a funcao de printar estado
	} 
	
	while((!(T->action_queue.empty())) && (T->action_queue.top()).t == cur_time) {
	    action A = T->action_queue.top();
	    T->action_queue.pop();
		
	    if (A.type == 1) {
		// Acessa a memória na paginação
		process cur_process = T->process_vec[A.process_id];
		acess cur_acess = cur_process.mem_acess[A.acess_id];
		P->access(cur_acess.pos);		
	    } else if (A.type == 2) {
		// Inicializa um processo
		process cur_process = T->process_vec[A.process_id];
		M->insert(A.process_id, cur_process.b);
	    } else if (A.type == 3) {
		// Finaliza um processo
		M->remove(A.process_id);
	    } else if (A.type == 4) {
		// Compacta
	    } else {
		cerr << "Tipo de acao nao valido " << A.type << endl;
		exit(-1);
	    }	
	}
	
	if (cur_time == end_time) {
	    // desativa a funcao de printar estado
	}
    }   
}

int main(int argc, char * argv[]) {
    trace * cur_trace;
    int mem_type = -1;
    int pag_type = -1;
    cout << "Para interagir com o prompt voce deve usar os comandos: " << endl;
    cout << "    carrega <arquivo>\n    espaco <num>\n    substitui <num>\n    executa <intervalo>\n    sai" << endl;
    cout << "Todos especificados no enunciado do EP3" << endl;
    cout << "Esperando comandos: " << endl;
    

    while (true) {
	string s;
	cout << "Comando: ";
	fflush(stdout);
	cin >> s;
	if (s == "carrega") {
	    string file_name;
	    cin >> file_name;
	    cur_trace = load_file(file_name);
	    cout << "Arquivo " << file_name << " carregado" << endl;
	} else if (s == "espaco") {
	    // Change de algortihm that manages memory
	    cin >> mem_type;
	    if (mem_type < 1 || mem_type > 3) {
		cout << "O tipo informado nao eh valido" << endl;
	    }
	    else cout << "Algortimo de gerenciamento de memoria " << mem_type << " escolhido" << endl;
	} else if (s == "substitui") {
	    // Change de algorithm that manages pages
	    cin >> pag_type;
	    if (pag_type < 1 || pag_type > 4) {
		cout << "O tipo informado nao eh valido" << endl;
	    }
	    else cout << "Algortimo de substituicao de pagina " << pag_type << " escolhido" << endl;
	} else if (s == "executa") {
	    int start_time, end_time;
	    cin >> start_time >> end_time;
	    if (mem_type == -1 || pag_type == -1)
		cerr << "Voce deve informar o tipo de simulador a ser executado" << endl;
	    else {
		// Executes the algorithm printing the states from start_time to end_time
		cout << "Simulando, imprimindo na stderr de " << start_time << " ate " << end_time << endl;
		simulate(cur_trace, mem_type, pag_type, start_time, end_time);
	    }
	} else if (s == "sai") {
	    break;
	} else {	    
	    cerr << "Comando nao suportado" << endl;
	}
    }
}
