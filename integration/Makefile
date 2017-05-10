.PHONY: default
default: A

A: outA.txt outB.txt

outA.txt: mainA
	./mainA > outA.txt

outB.txt: mainB
	./mainB > outB.txt

mainA: mainA.o adapt.o
	g++ -std=c++11 mainA.o adapt.o -o mainA

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c

mainB: mainB.o adapt.o
	g++ -std=c++11 mainB.o adapt.o -o mainB

mainB.o: mainB.cpp
	g++ -std=c++11 mainB.cpp -c

adapt.o: adapt.cpp
	g++ -std=c++11 adapt.cpp -c

.PHONY: clean

clean:
	rm -f *.o out* *.png mainA mainB
