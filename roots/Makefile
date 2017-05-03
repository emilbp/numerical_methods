.PHONY: default
default: A

A: outA.txt
	cat outA.txt

outA.txt: mainA
	./mainA > outA.txt

mainA: mainA.o newton.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o
	g++ -std=c++11 mainA.o newton.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

newton.o: newton.cpp
	g++ -std=c++11 newton.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA
