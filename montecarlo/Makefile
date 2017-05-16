.PHONY: default
default: A

A: outA.txt plotB.png

plotB.png: plot.gpi outB.txt Makefile
	gnuplot $<

outA.txt: mainA
	./mainA > outA.txt

outB.txt: mainB
	./mainB > outB.txt

mainA: mainA.o montecarlo.o
	g++ -std=c++11 mainA.o montecarlo.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

mainB: mainB.o
	g++ -std=c++11 mainB.o montecarlo.o -o mainB -larmadillo

mainB.o: mainB.cpp
	g++ -std=c++11 mainB.cpp -c -larmadillo 

montecarlo.o: montecarlo.cpp
	g++ -std=c++11 montecarlo.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* *.png mainA
