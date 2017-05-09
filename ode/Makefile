.PHONY: default
default: A

A: plot.png

plot.png: plot.gpi outA.txt Makefile
	gnuplot $<

outA.txt: mainAB
	./mainAB > outA.txt

mainAB: mainAB.o ode.o
	g++ -std=c++11 mainAB.o ode.o -o mainAB -larmadillo

mainAB.o: mainAB.cpp
	g++ -std=c++11 mainAB.cpp -c -larmadillo

ode.o: ode.cpp
	g++ -std=c++11 ode.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* *.png mainAB
