.PHONY: all clean

all:
	g++ -std=c++11 main.cpp -o falpha
	
clean:
	rm -rf falpha

	
