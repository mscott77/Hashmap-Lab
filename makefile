all:
	g++ -std=c++11 -o lab9 Hashmap.cpp main.cpp WordCounter.cpp 

clean:
	rm -f details.txt
	rm -f turnin.txt
	rm -f out_file*.txt
	rm -f lab9
