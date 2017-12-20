#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef enum{
	T_LOAD1,
	T_LOAD2,
	T_LOAD3,
	T_LOAD4,
	T_STORE1,
	T_STORE2,
	T_STORE3,
			T_BR1,
			T_BR2,
			T_BR3,
			T_ARITH1,
			T_ARITH2,
			T_ARITH3,
			T_ARITH4,
			T_ARITH5,
			T_ARITH6,
			T_ARITH7,
			T_ARITH8,
			T_ARITH9,
			T_ARITH10,
}inst_type;

//get type with granularity level 0
inst_type get_type_g0(string inst){
	switch(inst){
		//loads
		case "lda": case "ldah":
			return T_LOAD1;
		case "ldbu": case "ldl": case "ldq": case "ldwu":
			return T_LOAD2;
		case "ldqu":
			return T_LOAD3;
		case "ldll": case "ldql":
			return T_LOAD4;
			
		//stores
		case "stlc": case "stqc":
			return T_STORE1;
		case "stb": case "stl": case "stq": case "stw":
			return T_STORE2;
		case "stqu":
			return T_STORE3;
			
		//branches
		case "beq": case "bge": case "bgt": case "blbc": case "blbs": case "ble": case "blt": case "bne":
			return T_BR1;
		case "br": case "bsr":
			return T_BR2;
		case "jmp": case "jsr": case "ret": case "jsrc":
			return T_BR3;
		
		//arithmetic
		case "addl": case "subl":
			return T_ARITH1;
		case "s4addl": case "s8addl": case "s4subl": case "s8subl":
			return T_ARITH2;
		case "addq": case "subq":
			return T_ARITH3;
		case "s4addq": case "s8addq": case "s4subq": case "s8subq":
			return T_ARITH4;
		case "cmpeq": case "cmple": case "cmplt": case "cmpule": case "cmpult":
			return T_ARITH5;
		case "cltz": case "ctpop": case "cttz":
			return T_ARITH6;
		case "mull":
			return T_ARITH7;
		case "mulq": case "umulh":
			return T_ARITH8;
			
	}
}
/*
 
 */

class Inst{
public:
	string name;
};

static vector<string> inst_list;
static map<string, int> hist_all;

void scan(){
	ifstream in("inst.txt");
	if(!in.is_open()){
		printf("Could not open file.\n");
		exit(-1);
	}
	
	inst_list.clear();
	string inst;
	while(in >> inst){
		inst_list.push_back(inst);
	}
}

void build_hist_all(){
	hist_all.clear();
	for(auto it:inst_list){
		hist_all[it]++;
	}
}

void print(){
	for(auto it:inst_list){
		cout << it << endl;
	}
}

void print_hist_all(){
	for(auto it:hist_all){
		cout << it.first << '\t' << it.second << endl;
	}
}

int main(int argc, char** argv){
	scan();
	build_hist_all();
	print_hist_all();
	
	return 0;
}
