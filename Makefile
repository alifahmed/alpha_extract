.PHONY: all clean

all:
	g++ -std=c++11 main.cpp -o falpha -O0 -Wall -g
	
clean:
	rm -rf falpha

	
