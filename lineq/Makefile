.PHONY: default
default: A

A: outA.txt

outA.txt: mainA
	./mainA > outA.txt
	cat outA.txt

mainA: mainA.o qr_gs_dec.o qr_gs_solve.o
	g++ mainA.o qr_gs_dec.o qr_gs_solve.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ mainA.cpp -c -larmadillo

qr_gs_dec.o: qr_gs_dec.cpp
	g++ qr_gs_dec.cpp -c -larmadillo

qr_gs_solve.o: qr_gs_solve.cpp
	g++ qr_gs_solve.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA
