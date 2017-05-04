.PHONY: default
default: A

A: outA.txt outB.txt

outA.txt: mainA
	./mainA > outA.txt

outB.txt: mainB
	./mainB > outB.txt

mainA: mainA.o newton_mini.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o
	g++ -std=c++11 mainA.o newton_mini.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

newton_mini.o: newton_mini.cpp
	g++ -std=c++11 newton_mini.cpp -c -larmadillo

mainB: mainB.o quasi_newton.o
	g++ -std=c++11 mainB.o quasi_newton.o -o mainB -larmadillo

mainB.o: mainB.cpp
	g++ -std=c++11 mainB.cpp -c -larmadillo

quasi_newton.o: quasi_newton.cpp
	g++ -std=c++11 quasi_newton.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA mainB
