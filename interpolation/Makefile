GRAPH = /usr/bin/graph

.PHONY: default
default: A

A: outA1.svg outB.svg outC.svg out_Control.svg

outA1.svg: outA1.txt Makefile
	$(GRAPH) --top-label 'lspline with integral' \
	--output-format svg --x-label 'x' --y-label 'y' \
	< $<  > $@

outB.svg: outB.txt Makefile
	$(GRAPH) --top-label 'qspline with deriv and integ' \
	--output-format svg --x-label 'x' --y-label 'y' \
	< $<  > $@

outC.svg: outC.txt Makefile
	$(GRAPH) --top-label 'cspline with deriv and integ' \
	--output-format svg --x-label 'x' --y-label 'y' \
	< $<  > $@

out_Control.svg: out_Control.txt Makefile
	$(GRAPH) --top-label 'Analytical deriv and integ of cos(x)^2' \
	--output-format svg --x-label 'x' --y-label 'y' \
	< $<  > $@

outA1.txt: mainA1
	./mainA1 > outA1.txt

outB.txt: mainB
	./mainB > outB.txt

outC.txt: mainC
	./mainC > outC.txt

out_Control.txt: main_Control
	./main_Control > out_Control.txt

mainA1: mainA1.o lspline.o
	g++ -std=c++11 mainA1.o lspline.o -o mainA1

mainA1.o: mainA1.cpp
	g++ -std=c++11 mainA1.cpp -c

mainB: mainB.o qspline.o
	g++ -std=c++11 mainB.o qspline.o -o mainB

mainB.o: mainB.cpp
	g++ -std=c++11 mainB.cpp -c

mainC : mainC.o cspline.o
	g++ -std=c++11 mainC.o cspline.o -o mainC

mainC.o: mainC.cpp
	g++ -std=c++11 mainC.cpp -c

main_Control: main_Control.o
	g++ -std=c++11 main_Control.o -o main_Control

main_Control.o: main_Control.cpp
	g++ -std=c++11 main_Control.cpp -c

lspline.o: lspline.cpp
	g++ -std=c++11 lspline.cpp -c

qspline.o: qspline.cpp
	g++ -std=c++11 qspline.cpp -c

cspline.o: cspline.cpp
	g++ -std=c++11 cspline.cpp -c

.PHONY: clean
clean:
	rm -f *.o out* *.svg mainA1 mainB mainC main_Control
