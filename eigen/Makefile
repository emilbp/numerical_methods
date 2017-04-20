.PHONY: default
default: A

A: outA.txt

outA.txt: mainA
	./mainA > outA.txt
	cat outA.txt

mainA: mainA.o jacobi_eigen.o
	g++ mainA.o jacobi_eigen.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ mainA.cpp -c -larmadillo

jacobi_eigen.o: jacobi_eigen.cpp
	g++ jacobi_eigen.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA
