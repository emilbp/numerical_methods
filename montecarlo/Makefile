.PHONY: default
default: A

A: outA.txt

outA.txt: mainA
	./mainA > outA.txt

mainA: mainA.o montecarlo.o
	g++ -std=c++11 mainA.o montecarlo.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

montecarlo.o: montecarlo.cpp
	g++ -std=c++11 montecarlo.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* *.png mainA
