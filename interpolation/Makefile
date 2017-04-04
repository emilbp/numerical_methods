.PHONY: default
default: A

A: outA1.txt
	cat outA1.txt

outA1.txt: mainA1
	./mainA1 > outA1.txt

mainA1: mainA1.o lspline.o
	g++ -std=c++11 mainA1.o lspline.o -o mainA1

mainA1.o: mainA1.cpp
	g++ -std=c++11 mainA1.cpp -c

lspline.o: lspline.cpp
	g++ -std=c++11 lspline.cpp -c

.PHONY: clean
clean:
	rm -f *.o out* mainA1
