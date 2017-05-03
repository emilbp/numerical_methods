.PHONY: default
default: A

A: outA.txt outB.txt

outA.txt: mainA
	./mainA > outA.txt

outB.txt: mainB
	./mainB > outB.txt
	cat outB.txt

mainA: mainA.o newton.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o
	g++ -std=c++11 mainA.o newton.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

newton.o: newton.cpp
	g++ -std=c++11 newton.cpp -c -larmadillo

mainB: mainB.o newton.o newton_analytic.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o
	g++ -std=c++11 mainB.o newton_analytic.o newton.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o -o mainB -larmadillo

mainB.o: mainB.cpp
	g++ -std=c++11 mainB.cpp -c -larmadillo

newton_analytic.o: newton_analytic.cpp
	g++ -std=c++11 newton_analytic.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA mainB
