.PHONY: default
default: A

A: plot.png

plot.png: plot.gpi outA.txt Makefile
	gnuplot $<

outA.txt: mainA
	./mainA > outA.txt

mainA: mainA.o lsfit.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o ../lineq/qr_gs_inverse.o
	g++ -std=c++11 mainA.o lsfit.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o ../lineq/qr_gs_inverse.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

lsfit.o: lsfit.cpp
	g++ -std=c++11 lsfit.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* *.png mainA
