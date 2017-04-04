.PHONEY: default
default: A C

C: check

A: out.txt
	cat out.txt

out.txt: main
	./main > out.txt

main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

.PHONEY: clean
clean:
	rm -f *.o main out* correct.txt

.PHONEY: check
check: out.txt correct.txt
	diff --brief out.txt correct.txt
	echo "Test passed"
correct.txt:
	echo "Hello, $(shell whoami)" > correct.txt
