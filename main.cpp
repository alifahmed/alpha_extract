#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef enum{
	T_UNDEF,
	T_LOAD,
	T_STORE,
	T_BR,
	T_LLATENCY,		//long latency instructions
	T_IARITH,		//1 cycle latency
	T_FARITH		//4 cycle latency
}inst_type1;

map<string, inst_type1> inst_type1_map;
map<inst_type1, string> type_name_map;

void init_type1_map(){
	//init type_name_map
	type_name_map[T_UNDEF] = "T_UNDEF";
	type_name_map[T_LOAD] = "T_LOAD";
	type_name_map[T_STORE] = "T_STORE";
	type_name_map[T_BR] = "T_BR";
	type_name_map[T_IARITH] = "T_IARITH";
	type_name_map[T_FARITH] = "T_FARITH";
	type_name_map[T_LLATENCY] = "T_LLATENCY";
		
	//loads
	inst_type1_map["lda"] = T_LOAD;
	inst_type1_map["ldah"] = T_LOAD;
	inst_type1_map["ldbu"] = T_LOAD;
	inst_type1_map["ldl"] = T_LOAD;
	inst_type1_map["ldq"] = T_LOAD;
	inst_type1_map["ldq_u"] = T_LOAD;
	inst_type1_map["ldwu"] = T_LOAD;
	inst_type1_map["ldl_l"] = T_LOAD;
	inst_type1_map["ldq_l"] = T_LOAD;
	inst_type1_map["ldf"] = T_LOAD;
	inst_type1_map["ldg"] = T_LOAD;
	inst_type1_map["lds"] = T_LOAD;
	inst_type1_map["ldt"] = T_LOAD;
	
	//stores
	inst_type1_map["stl_c"] = T_STORE;
	inst_type1_map["stq_c"] = T_STORE;
	inst_type1_map["stb"] = T_STORE;
	inst_type1_map["stl"] = T_STORE;
	inst_type1_map["stq"] = T_STORE;
	inst_type1_map["stw"] = T_STORE;
	inst_type1_map["stq_u"] = T_STORE;
	inst_type1_map["stf"] = T_STORE;
	inst_type1_map["stg"] = T_STORE;
	inst_type1_map["sts"] = T_STORE;
	inst_type1_map["stt"] = T_STORE;
	
	//branches
	inst_type1_map["beq"] = T_BR;
	inst_type1_map["bge"] = T_BR;
	inst_type1_map["bgt"] = T_BR;
	inst_type1_map["blbc"] = T_BR;
	inst_type1_map["blbs"] = T_BR;
	inst_type1_map["ble"] = T_BR;
	inst_type1_map["blt"] = T_BR;
	inst_type1_map["bne"] = T_BR;
	inst_type1_map["br"] = T_BR;
	inst_type1_map["bsr"] = T_BR;
	inst_type1_map["jmp"] = T_BR;
	inst_type1_map["jsr"] = T_BR;
	inst_type1_map["ret"] = T_BR;
	inst_type1_map["jsrc"] = T_BR;
	inst_type1_map["fbeq"] = T_BR;
	inst_type1_map["fbge"] = T_BR;
	inst_type1_map["fbgt"] = T_BR;
	inst_type1_map["fble"] = T_BR;
	inst_type1_map["fblt"] = T_BR;
	inst_type1_map["fbne"] = T_BR;
	
	//integer arithmetic
	inst_type1_map["nop"] = T_IARITH;
	inst_type1_map["unop"] = T_IARITH;
	inst_type1_map["mov"] = T_IARITH;
	inst_type1_map["clr"] = T_IARITH;
	inst_type1_map["halt"] = T_IARITH;
	inst_type1_map["addl"] = T_IARITH;
	inst_type1_map["subl"] = T_IARITH;
	inst_type1_map["s4addl"] = T_IARITH;
	inst_type1_map["s8addl"] = T_IARITH;
	inst_type1_map["s4subl"] = T_IARITH;
	inst_type1_map["s8subl"] = T_IARITH;
	inst_type1_map["addq"] = T_IARITH;
	inst_type1_map["subq"] = T_IARITH;
	inst_type1_map["s4addq"] = T_IARITH;
	inst_type1_map["s8addq"] = T_IARITH;
	inst_type1_map["s4subq"] = T_IARITH;
	inst_type1_map["s8subq"] = T_IARITH;
	inst_type1_map["cmpeq"] = T_IARITH;
	inst_type1_map["cmple"] = T_IARITH;
	inst_type1_map["cmplt"] = T_IARITH;
	inst_type1_map["cmpule"] = T_IARITH;
	inst_type1_map["cmpult"] = T_IARITH;
	inst_type1_map["ctlz"] = T_IARITH;
	inst_type1_map["ctpop"] = T_IARITH;
	inst_type1_map["cttz"] = T_IARITH;
	inst_type1_map["sextl"] = T_IARITH;
	
	//integer multiplication
	inst_type1_map["mull"] = T_LLATENCY;
	inst_type1_map["mulq"] = T_LLATENCY;
	inst_type1_map["umulh"] = T_LLATENCY;
	
	//logical
	inst_type1_map["and"] = T_IARITH;
	inst_type1_map["or"] = T_IARITH;
	inst_type1_map["andnot"] = T_IARITH;
	inst_type1_map["not"] = T_IARITH;
	inst_type1_map["bic"] = T_IARITH;
	inst_type1_map["bis"] = T_IARITH;
	inst_type1_map["eqv"] = T_IARITH;
	inst_type1_map["ornot"] = T_IARITH;
	inst_type1_map["xor"] = T_IARITH;
	inst_type1_map["cmoveq"] = T_IARITH;
	inst_type1_map["cmovge"] = T_IARITH;
	inst_type1_map["cmovgt"] = T_IARITH;
	inst_type1_map["cmovlbc"] = T_IARITH;
	inst_type1_map["cmovlbs"] = T_IARITH;
	inst_type1_map["cmovle"] = T_IARITH;
	inst_type1_map["cmovlt"] = T_IARITH;
	inst_type1_map["cmovne"] = T_IARITH;
	
	//shift and byte manipulation
	inst_type1_map["sll"] = T_IARITH;
	inst_type1_map["srl"] = T_IARITH;
	inst_type1_map["sra"] = T_IARITH;
	inst_type1_map["cmpbge"] = T_IARITH;
	inst_type1_map["extbl"] = T_IARITH;
	inst_type1_map["extwl"] = T_IARITH;
	inst_type1_map["extll"] = T_IARITH;
	inst_type1_map["extql"] = T_IARITH;
	inst_type1_map["extwh"] = T_IARITH;
	inst_type1_map["extlh"] = T_IARITH;
	inst_type1_map["extqh"] = T_IARITH;
	inst_type1_map["insbl"] = T_IARITH;
	inst_type1_map["inswl"] = T_IARITH;
	inst_type1_map["insll"] = T_IARITH;
	inst_type1_map["insql"] = T_IARITH;
	inst_type1_map["inswh"] = T_IARITH;
	inst_type1_map["inslh"] = T_IARITH;
	inst_type1_map["insqh"] = T_IARITH;
	inst_type1_map["zap"] = T_IARITH;
	inst_type1_map["mskbl"] = T_IARITH;
	inst_type1_map["mskwl"] = T_IARITH;
	inst_type1_map["mskll"] = T_IARITH;
	inst_type1_map["mskql"] = T_IARITH;
	inst_type1_map["mskwh"] = T_IARITH;
	inst_type1_map["msklh"] = T_IARITH;
	inst_type1_map["mskqh"] = T_IARITH;
	inst_type1_map["sextb"] = T_IARITH;
	inst_type1_map["sextw"] = T_IARITH;
	inst_type1_map["zapnot"] = T_IARITH;
	
	//floating arithmetic
	inst_type1_map["fclr"] = T_FARITH;
	inst_type1_map["fabs"] = T_FARITH;
	inst_type1_map["fmov"] = T_FARITH;
	inst_type1_map["fneg"] = T_FARITH;
	inst_type1_map["fnop"] = T_FARITH;
	inst_type1_map["cpys"] = T_FARITH;
	inst_type1_map["cpyse"] = T_FARITH;
	inst_type1_map["cpysn"] = T_FARITH;
	inst_type1_map["cvtlq"] = T_FARITH;
	inst_type1_map["cvtql"] = T_FARITH;
	inst_type1_map["mf_fpcr"] = T_FARITH;
	inst_type1_map["mt_fpcr"] = T_FARITH;
	inst_type1_map["addf"] = T_FARITH;
	inst_type1_map["addg"] = T_FARITH;
	inst_type1_map["adds"] = T_FARITH;
	inst_type1_map["addt"] = T_FARITH;
	inst_type1_map["cvtdg"] = T_FARITH;
	inst_type1_map["cvtgd"] = T_FARITH;
	inst_type1_map["cvtgf"] = T_FARITH;
	inst_type1_map["cvtgg"] = T_FARITH;
	inst_type1_map["cvtqf"] = T_FARITH;
	inst_type1_map["cvtqg"] = T_FARITH;
	inst_type1_map["cvtqs"] = T_FARITH;
	inst_type1_map["cvtqt"] = T_FARITH;
	inst_type1_map["cvtst"] = T_FARITH;
	inst_type1_map["cvtst"] = T_FARITH;
	inst_type1_map["cvttq"] = T_FARITH;
	inst_type1_map["cvttq"] = T_FARITH;
	inst_type1_map["cvtts"] = T_FARITH;
	inst_type1_map["ftois"] = T_FARITH;
	inst_type1_map["ftoit"] = T_FARITH;
	inst_type1_map["itoff"] = T_FARITH;
	inst_type1_map["itofs"] = T_FARITH;
	inst_type1_map["itoft"] = T_FARITH;
	inst_type1_map["fcmoveq"] = T_FARITH;
	inst_type1_map["fcmovge"] = T_FARITH;
	inst_type1_map["fcmovgt"] = T_FARITH;
	inst_type1_map["fcmovle"] = T_FARITH;
	inst_type1_map["fcmovlt"] = T_FARITH;
	inst_type1_map["fcmovne"] = T_FARITH;
	inst_type1_map["cmpgeq"] = T_FARITH;
	inst_type1_map["cmpgle"] = T_FARITH;
	inst_type1_map["cmpglt"] = T_FARITH;
	inst_type1_map["cmpteq"] = T_FARITH;
	inst_type1_map["cmptle"] = T_FARITH;
	inst_type1_map["cmptlt"] = T_FARITH;
	inst_type1_map["cmptun"] = T_FARITH;
	inst_type1_map["subf"] = T_FARITH;
	inst_type1_map["subg"] = T_FARITH;
	inst_type1_map["subs"] = T_FARITH;
	inst_type1_map["subt"] = T_FARITH;
	inst_type1_map["negf"] = T_FARITH;
	inst_type1_map["negg"] = T_FARITH;
	inst_type1_map["negs"] = T_FARITH;
	inst_type1_map["negt"] = T_FARITH;
	inst_type1_map["negq"] = T_FARITH;
	inst_type1_map["negl"] = T_FARITH;
	
	
	//floating multiplication
	inst_type1_map["mulf"] = T_FARITH;
	inst_type1_map["mulg"] = T_FARITH;
	inst_type1_map["muls"] = T_FARITH;
	inst_type1_map["mult"] = T_FARITH;
	
	//floating division
	inst_type1_map["divf"] = T_LLATENCY;
	inst_type1_map["divg"] = T_LLATENCY;
	inst_type1_map["divs"] = T_LLATENCY;
	inst_type1_map["divt"] = T_LLATENCY;
	
	//floating sqrt
	inst_type1_map["sqrtf"] = T_LLATENCY;
	inst_type1_map["sqrtg"] = T_LLATENCY;
	inst_type1_map["sqrts"] = T_LLATENCY;
	inst_type1_map["sqrtt"] = T_LLATENCY;
	
	//others - not clear
	inst_type1_map["wruniq"] = T_LLATENCY;
	inst_type1_map["rduniq"] = T_LLATENCY;
	inst_type1_map["imb"] = T_LLATENCY;
	inst_type1_map["mb"] = T_LLATENCY;
	inst_type1_map["wmb"] = T_LLATENCY;
	inst_type1_map["callsys"] = T_LLATENCY;
	inst_type1_map["wh64"] = T_LLATENCY;
	inst_type1_map["amask"] = T_LLATENCY;
	inst_type1_map["excb"] = T_LLATENCY;
	inst_type1_map["implver"] = T_LLATENCY;
	inst_type1_map["gentrap"] = T_LLATENCY;
	inst_type1_map["rpcc"] = T_LLATENCY;
}

static vector<string> inst_list;
static map<string, int> hist_all;
static map<inst_type1, int> hist_g1;

void scan(){
	ifstream in("inst.txt");
	if(!in.is_open()){
		printf("Could not open file.\n");
		exit(-1);
	}
	
	inst_list.clear();
	string inst;
	while(in >> inst){
		//check validity
		if(inst_type1_map.find(inst) == inst_type1_map.end()){
			printf("Instruction not found: %s", inst.c_str());
			exit(-1);
		}
		
		inst_list.push_back(inst);
	}
}

void build_hist_all(){
	hist_all.clear();
	for(auto it:inst_list){
		hist_all[it]++;
	}
}

void build_hist_g1(){
	hist_g1.clear();
	for(auto it:inst_list){
		hist_g1[inst_type1_map[it]]++;
	}
}

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

void print_hist_g1(){
	for(auto it:hist_g1){
		cout << type_name_map[it.first] << '\t' << it.second << endl;
	}
}

int main(int argc, char** argv){
	init_type1_map();
	scan();
	build_hist_g1();
	print_hist_g1();
	cout << "Total inst:\t" << inst_list.size() << endl;
	return 0;
}
