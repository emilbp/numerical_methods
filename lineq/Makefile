.PHONY: default
default: A

A: outA.txt outB.txt

outA.txt: mainA
	./mainA > outA.txt

outB.txt: mainB
	./mainB > outB.txt

mainA: mainA.o qr_gs_dec.o qr_gs_solve.o
	g++ mainA.o qr_gs_dec.o qr_gs_solve.o -o mainA -larmadillo

mainB: mainB.o qr_gs_dec.o qr_gs_inverse.o qr_gs_solve.o
	g++ mainB.o qr_gs_dec.o qr_gs_inverse.o qr_gs_solve.o -o mainB -larmadillo

mainA.o: mainA.cpp
	g++ mainA.cpp -c -larmadillo

mainB.o: mainB.cpp
	g++ mainB.cpp -c -larmadillo

qr_gs_dec.o: qr_gs_dec.cpp
	g++ qr_gs_dec.cpp -c -larmadillo

qr_gs_solve.o: qr_gs_solve.cpp
	g++ qr_gs_solve.cpp -c -larmadillo

qr_gs_inverse.o: qr_gs_inverse.cpp
	g++ qr_gs_inverse.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA mainB
