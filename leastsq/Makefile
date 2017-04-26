.PHONY: default
default: A

A: plot.svg

plot.svg: outA.txt Makefile
	graph --display-type svg \
	--width 0.7 --height 0.7 \
	--x-label "x" --y-label "F\sbc\eb(x), F\sbc-dc\eb(x), F\sbc+dc\eb(x)" \
	--top-label "LS fit with c +- deltac" \
	outA.txt > plot.svg

outA.txt: mainA
	./mainA > outA.txt

mainA: mainA.o
	g++ -std=c++11 mainA.o -o mainA -larmadillo

mainA.o: mainA.cpp
	g++ -std=c++11 mainA.cpp -c -larmadillo

.PHONY: clean

clean:
	rm -f *.o out* *.svg mainA
