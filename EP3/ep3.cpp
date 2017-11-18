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
    trace * ret = new trace;
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
        action A = action(4, atoi(objs[0].c_str()), -1, -1);
        ret->action_queue.push(A);
        }
        
    } else {
        process p;
        int PID = ret->process_vec.size();
        p.t0 = atoi(objs[0].c_str());
        p.tf = atoi(objs[1].c_str());
        p.b  = atoi(objs[2].c_str());
        p.name = objs[3];
        action initialize = action(2, p.t0, PID, -1);
        action finalize   = action(3, p.tf, PID, -1);
        
        for (int i = 4; i < (int)objs.size(); i += 2) {
        acess A;
        int AID = p.mem_acess.size();
        
        A = acess(atoi(objs[i].c_str()), atoi(objs[i + 1].c_str()));
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

void simulate(trace * T, int mem_type, int pag_type, int print_time) {
    // Cria as classes dos tipos que você quer
    
    char * virt_dir = (char *) malloc(sizeof(char) * 10);
    char * real_dir = (char *) malloc(sizeof(char) * 10);
    
    strcpy(virt_dir, "ep3.vir");
    strcpy(real_dir, "ep3.mem");


    MemoryMen * M;
    BiFile * VirtualMem = new BiFile(T->virt, virt_dir);
    PageMen * P;
    BiFile * RealMem = new BiFile(T->total, real_dir);
    int *pageMap = new int[T->virt/T->p];

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

    
    for (int cur_time = 0; !(T->action_queue.empty()); cur_time++) {
    // Tempo atual eh cur_time

        if ((cur_time%print_time) == 0) {
            //printa estado
        } 
    
        while((!(T->action_queue.empty())) && (T->action_queue.top()).t == cur_time) {
            action A = T->action_queue.top();
            T->action_queue.pop();
    
            cerr << "ACAO type: " << A.type << " t: " << A.t << " PID: " << A.process_id << " AID: " << A.acess_id << endl;
    
        
            if (A.type == 1) {
                // Acessa a memória na paginação
                process cur_process = T->process_vec[A.process_id];
                acess cur_acess = cur_process.mem_acess[A.acess_id];
                P->access(cur_acess.pos);       
            } else if (A.type == 2) {
                // Inicializa um processo
                process cur_process = T->process_vec[A.process_id];
                if (!M->insert(A.process_id, cur_process.b)) {
                    M->compact(pageMap);
                    P->compact(pageMap);
                    if (!M->insert(A.process_id, cur_process.b)) {
                        cerr << "nao ha memoria suficiente para simular\n";
                        return;
                    }
                }
            } else if (A.type == 3) {
                // Finaliza um processo
                P->remove(M->translate(A.process_id, 0), M->translate(A.process_id, M->size(A.process_id) - 1));
                M->remove(A.process_id);
            } else if (A.type == 4) {
                // Compacta
                M->compact(pageMap);
                P->compact(pageMap);
            } else {
                cerr << "Tipo de acao nao valido " << A.type << endl;
                exit(-1);
            }   
        }
    }
    M->printll();
}

int main(int argc, char * argv[]) {
    
    trace * cur_trace;
    int mem_type = -1;
    int pag_type = -1;
    
    
    cur_trace = load_file("trace-file.txt");
    simulate(cur_trace, 1, 2, 3);
    return 0;
    
    cout << "Para interagir com o prompt voce deve usar os comandos: " << endl;
    cout << "    carrega <arquivo>\n    espaco <num>\n    substitui <num>\n    executa <intervalo>\n    sai" << endl;
    cout << "Todos especificados no enunciado do EP3" << endl;
    cout << "Esperando comandos: " << endl;
    

    while (true) {
        string s;
        vector<string> vs;
        cout << "Comando: ";
        fflush(stdout);
        getline(cin, s);
        vs = stringToVec(s);
        s = vs[0];
        if (s == "carrega") {
            string file_name;
            file_name = vs[1];
            cur_trace = load_file(file_name);
            cout << "Arquivo " << file_name << " carregado" << endl;
        } else if (s == "espaco") {
            // Change de algortihm that manages memory
            mem_type = atoi(vs[1].c_str());
            if (mem_type < 1 || mem_type > 3) {
                cout << "O tipo informado nao eh valido" << endl;
            }
            else cout << "Algortimo de gerenciamento de memoria " << mem_type << " escolhido" << endl;
        } else if (s == "substitui") {
            // Change de algorithm that manages pages
            pag_type = atoi(vs[1].c_str());
            if (pag_type < 1 || pag_type > 4) {
                cout << "O tipo informado nao eh valido" << endl;
            }
            else cout << "Algortimo de substituicao de pagina " << pag_type << " escolhido" << endl;
        } else if (s == "executa") {
            int print_time;
            print_time = atoi(vs[1].c_str());
            if (mem_type == -1 || pag_type == -1)
                cerr << "Voce deve informar o tipo de simulador a ser executado" << endl;
            else {
                // Executes the algorithm printing the states from start_time to end_time
                cout << "Simulando, imprimindo na stderr de " << print_time << " em " << print_time << endl;
                simulate(cur_trace, mem_type, pag_type, print_time);
            }
        } else if (s == "sai") {
            break;
        } else {        
            cerr << "Comando nao suportado" << endl;
        }
    }
}