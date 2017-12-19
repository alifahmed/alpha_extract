#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv){
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("Could not open file.\n");
		return -1;
	}
	
	return 0;
}
