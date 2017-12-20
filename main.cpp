#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef enum{
	T_LOAD,
	T_STORE,
	T_BR,
	T_SHIFT,
	T_IMUL,
	T_IARITH,
	T_FARITH,
	T_FMUL,
	T_FDIV
}inst_type1;

/*typedef enum{
	T_LOAD,
	T_STORE,
	T_BR,
	T_IARITH,
	T_FARITH
}inst_type2;*/

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
	T_LOGIC1,
	T_LOGIC2,
	T_LOGIC3,
	T_BYTE1,
	T_FLOAD1,
	T_FSTORE1,
	T_FBR1,
	T_FARITH1,
	T_FARITH2,
	T_FARITH3,
	T_FARITH4,
	T_UNDEF			
}inst_type0;

//get type with granularity level 0
inst_type0 get_type_g0(string inst){
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
			
		//logical
		case "and": case "bic": case "bis": case "eqv": case "ornot": case "xor":
			return T_LOGIC1;
		case "cmoveq": case "cmovge": case "cmovgt": case "cmovlbc": case "cmovlbs": case "cmovle": case "cmovlt": case "cmovne":
			return T_LOGIC2;
		case "sll": case "srl": case "sra":
			return T_LOGIC3;
			
		//byte manipulation
		case "cmpbge": case "extbl": case "extwl": case "extll": case "extql": case "extwh": case "extlh": case "extqh":
		case "insbl": case "inswl": case "insll": case "insql": case "inswh": case "inslh": case "insqh": case "zap":
		case "mskbl": case "mskwl": case "mskll": case "mskql": case "mskwh": case "msklh": case "mskqh": case "sextb":
		case "sextw": case "zapnot":
			return T_BYTE1;
			
		//floating
		case "ldf": case "ldg": case "lds": case "ldt":
			return T_FLOAD1;
		case "stf": case "stg": case "sts": case "stt":
			return T_FSTORE1;
		case "fbeq": case "fbge": case "fbgt": case "fble": case "fblt": case "fbne":
			return T_FBR1;
		case "cpys": case "cpyse": case "cpysn": case "cvtlq": case "cvtql": case "mffpcr": case "mtfpcr":
		case "addf": case "addg": case "adds": case "addt": case "cvtdg": case "cvtgd": case "cvtgf": case "cvtgq":
		case "cvtqf": case "cvtqg": case "cvtqs": case "cvtqt": case "cvtst": case "cvttq": case "cvtts":
		case "ftois": case "ftoit": case "itoff": case "itofs": case "itoft":
		case "fcmoveq": case "fcmovge": case "fcmovgt": case "fcmovle": case "fcmovlt": case "fcmovne":
		case "cmpgeq": case "cmpgle": case "cmpglt": case "cmpteq": case "cmptle": case "cmptlt": case "cmptun":
		case "subf": case "subg": case "subs": case "subt":
			return T_FARITH1;
		case "divf": case "divg": case "divs": case "divt":
			return T_FARITH2;
		case "mulf": case "mulg": case "muls": case "mult":
			return T_FARITH3;
		case "sqrtf": case "sqrtg": case "sqrts": case "sqrtt":
			return T_FARITH4;
		
		//not found
		default:
			return T_UNDEF;
	}
}


class Inst{
public:
	string name;
};

static vector<string> inst_list;
static map<string, int> hist_all;
static map<inst_type0, int> hist_g0;
static map<inst_type1, int> hist_g1;
//static map<inst_type2, int> hist_g2;


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

void build_hist_g0(){
	hist_g0.clear();
	for(auto it:inst_list){
		hist_g0[get_type_g0(it)]++;
	}
}

/*void build_hist_g1(){
	hist_g1.clear();
	for(auto it:inst_list){
		hist_g1[it]++;
	}
}

void build_hist_g2(){
	hist_g2.clear();
	for(auto it:inst_list){
		hist_g2[it]++;
	}
}*/

void print_inst(){
	for(auto it:inst_list){
		cout << it << endl;
	}
}

void print_hist_all(){
	for(auto it:hist_all){
		cout << it.first << '\t' << it.second << endl;
	}
}

void print_hist_g0(){
	for(auto it:hist_g0){
		cout << it.second << endl;
	}
}

int main(int argc, char** argv){
	scan();
	build_hist_all();
	print_hist_all();
	build_hist_g0();
	print_hist_g0();
	
	return 0;
}
