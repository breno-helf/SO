#include <bits/stdc++.h>
using namespace std;

/* trace.hpp
   This file has all the structs you need to manage to read and
   store the information of the trace file
*/

// Stores a memory acess
struct acess {
    int pos;
    double t;
    acess(int POS = 0, double T = 0.0):
	pos(POS), t(T) {}    

    bool operator < (const acess ot) const {
	return t < ot.t;
    }

    bool operator > (const acess ot) const {
	return t > ot.t;
    }
};

// Store a process
struct process {
    double t0, tf;
    int b;
    string name;
    priority_queue<acess, vector<acess>, greater<acess> > mem_acess;

    process(double T0 = 0.0, double TF = 0.0, int B = 0, string NAME = "") {
	t0 = T0;
	tf = TF;
	b  = B;
	name = NAME;		
    };    

    bool operator < (const process ot) const {
	return t0 < ot.t0;
    }

    bool operator > (const process ot) const {
	return t0 > ot.t0;
    }
};

// Store the trace file
struct trace {
    int total, virt, s, p;
    priority_queue<process, vector<process>, greater<process> > process_queue;
    priority_queue<double, vector<double>, greater<double> > compact;
};
