.PHONY: default
default: A

A: outA.txt

outA.txt: mainA
	./mainA > outA.txt

mainA: mainA.o adapt_complex.o
	g++ -std=c++11 mainA.o adapt_complex.o -o mainA

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c

adapt_complex.o: adapt_complex.cpp
	g++ -std=c++11 adapt_complex.cpp -c

.PHONY: clean

clean:
	rm -f *.o out* *.png mainA
