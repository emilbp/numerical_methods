.PHONY: default
default: A

A: plot.png

plot.png: plot.gpi outA.txt Makefile
	gnuplot $<

outA.txt: mainA
	./mainA > outA.txt

mainA: mainA.o ode.o
	g++ -std=c++11 mainA.o ode.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

ode.o: ode.cpp
	g++ -std=c++11 ode.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* *.png mainA
