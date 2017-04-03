.PHONEY: default
default: A C

C:check

A:out.txt
	cat out.txt

out.txt: main
	./main > out.txt

main: main.o
	g++ -o main main.o

main.o: main.cc
	g++ -c main.cc -o main.o

.PHONEY:clean
clean:
	rm -f main.o main out.txt correct.txt

.PHONEY:check
check: out.txt correct.txt
	diff --brief out.txt correct.txt
	echo "Test passed"
correct.txt:
	echo "Hello, $(shell whoami)" > correct.txt
