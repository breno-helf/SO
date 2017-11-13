#include <bits/stdc++.h>
#include "trace.hpp"
using namespace std;

vector<string> stringToVec(string s) {
    vector<string> ret;
    string r = "";
    for (int i = 0; i < (int)s.size(); i++) {
	if (isspace(s[i])) r += s[i];
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
		ret->compact.push(atof(objs[1].c_str()));
	    }
	} else {
	    process p;
	    p.t0 = atof(objs[0].c_str());
	    p.tf = atof(objs[1].c_str());
	    p.b  = atoi(objs[2].c_str());
	    p.name = objs[3];
	    for (int i = 4; i < (int)objs.size(); i += 2) {
		acess A;
		A = acess(atoi(objs[i].c_str()), atof(objs[i + 1].c_str()));
		p.mem_acess.push(A);
	    }
	    ret->process_queue.push(p);
	}	
    }
    trace_file.close();
    
    return ret;
}

int main(int argc, char * argv[]) {
    trace * cur_trace;
    int type = -1;
    
    while (true) {
	string s;
	cin >> s;
	if (s == "carrega") {
	    string file_name;
	    cin >> file_name;
	    cur_trace = load_file(file_name);
	} else if (s == "espaço") {
	    // Define o numero de espaços
	} else if (s == "substitui") {
	    cin >> type;
	} else if (s == "executa") {
	    if (type == -1)
		cerr << "Voce deve informar o tipo de simulador a ser executado\n";
	    else {
		// Executa o algoritimo
	    }
	} else {
	    break;
	}
	fflush(stdout);
    }
}
