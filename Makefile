all: galgebra

galgebra: main.o
	g++ main.o -o galgebra

main.o: main.cpp
	g++ -c main.cpp -o main.o
