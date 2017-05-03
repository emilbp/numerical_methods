.PHONY: default
default: A

A: outA.txt

outA.txt: mainA
	./mainA > outA.txt
	cat outA.txt

mainA: mainA.o newton_mini.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o
	g++ -std=c++11 mainA.o newton_mini.o ../lineq/qr_gs_dec.o ../lineq/qr_gs_solve.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

newton_mini.o: newton_mini.cpp
	g++ -std=c++11 newton_mini.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA mainB
