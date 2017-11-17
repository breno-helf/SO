// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
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
    vector<acess> mem_acess;

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

/*
  Types:
  1 - Memory Acess 
  2 - Process Initialization
  3 - Process Finalization
  4 - Compact
     
  process_id is the position of the process in the trace vector
  acess_id is the position of the acess in the mem_acess vector (in the proces)
  when is compact both are -1
  when is process initialization / finalition acess_id is -1.
*/
struct action {
    int type;
    double t;
    int process_id;
    int acess_id;
    action(int TYPE = 0, double T = 0.0, int PID = -1, int AID = -1) {
	type = TYPE;
	t = T;
	process_id = PID;
	acess_id = AID;
    }
    
    bool operator < (const action ot) const {
	return t < ot.t;
    }

    bool operator > (const action ot) const {
	return t > ot.t;
    }
};

// Store the trace file
struct trace {
    int total, virt, s, p;
    vector<process> process_vec;
    priority_queue<action, vector<action>, greater<action> > action_queue;    
};
