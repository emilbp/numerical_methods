.PHONY: default
default: A

A: outA.txt outB.txt outBtimes.txt

outA.txt: mainA
	./mainA > outA.txt

outB.txt: mainB
	./mainB > outB.txt

outBtimes.txt: mainB2
	./mainB2 > outBtimes.txt

mainA: mainA.o jacobi_eigen.o
	g++ mainA.o jacobi_eigen.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ mainA.cpp -c -larmadillo

jacobi_eigen.o: jacobi_eigen.cpp
	g++ jacobi_eigen.cpp -c -larmadillo

mainB: mainB.o jacobi_eigen_VbV.o
	g++ mainB.o jacobi_eigen_VbV.o -o mainB -larmadillo

mainB.o: mainB.cpp
	g++ mainB.cpp -c -larmadillo

jacobi_eigen_VbV.o: jacobi_eigen_VbV.cpp
	g++ jacobi_eigen_VbV.cpp -c -larmadillo

mainB2: mainB2.o
	g++ mainB2.o jacobi_eigen.o jacobi_eigen_VbV.o -o mainB2 -larmadillo

mainB2.o: mainB2.cpp
	g++ mainB2.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* mainA mainB mainB2
